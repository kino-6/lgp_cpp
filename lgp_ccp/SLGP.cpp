#include "SLGP.h"
#include "AggregateInfo.h"
#include "csv_parser.h"

SLGP::SLGP() {
	// seed
	rnd.seed(123);

	// stub
	this->NVariables = 9;
	this->NOperators = 4;
	this->NRegisters = NREGISTERS;
	this->NInputs = 3;
	this->NConstants = 2;
	this->NIndividuals = 200;
	this->NElite = 3;
	this->NGenes = 30;
	this->NGenesMin = 20;
	this->NGenesMax = 500;
	this->NTimes = 1000;
	this->PMutate = 0.2;
	this->PCrossOver = 0.8;
	this->tsize = 4;

	this->problem = new SLGP_Problem();

	this->pop.clear();
	this->pop.resize(this->NIndividuals);
	for (size_t i = 0; i < this->pop.size(); i++) {
		this->pop[i].code.resize(this->NGenes);
		this->pop[i].reg.resize(this->NRegisters);
		this->pop[i].fitness = this->problem->EvaluateIndividual(this->pop[i]);
		this->pop_sample_idx.push_back(i);
	}
}

SLGP::~SLGP() {
	this->pop.clear();
}

void SLGP::SLGP_Main() {
	std::vector<Individual> Temp;

	for (u64 i = 0; i < this->NTimes; i++) {
		cout << "-----------------------------------------" << endl;
		cout << "Generation : " << i << endl;
		cout << "-----------------------------------------" << endl;

		// ensure elite
		this->elite = SearchElite(this->pop);

		// renew population
		this->new_pop = this->pop;
		for (size_t i = 0; i < this->new_pop.size(); i+=2) {
			//cout << "i: " << i << endl;
			// Mutate
			if (rnd.randBool(this->PMutate)) {
				Mutate(this->new_pop[i]);
				Mutate(this->new_pop[i+1]);
			}

			// CrossOver
			if (rnd.randBool(this->PCrossOver)) {
				auto p1_idx = Tournament(this->pop, this->tsize);
				auto p2_idx = Tournament(this->pop, this->tsize);
				auto child = CrossOver(this->pop[p1_idx], this->pop[p2_idx]);
				this->new_pop[i] = child[0];
				this->new_pop[i+1] = child[1];
			}

			// ReGenration
			ReGeneration(this->new_pop[i]);
			ReGeneration(this->new_pop[i+1]);

			// re evaluate
			this->new_pop[i].fitness = this->problem->EvaluateIndividual(this->new_pop[i]);
			this->new_pop[i + 1].fitness = this->problem->EvaluateIndividual(this->new_pop[i + 1]);
		}

		// swap worst to elite
		SortPopulation(this->new_pop);
		auto swap_idx_start = this->new_pop.size() - 1;
		for (size_t i = 0; i < this->elite.size(); i++) {
			this->new_pop[swap_idx_start] = this->elite[i];
			swap_idx_start--;
		}

		// renew population
		Temp = this->pop; this->pop = this->new_pop; this->new_pop = Temp;
		Summary(this->pop);
	}
	this->elite = SearchElite(this->new_pop);
	print_individual(this->elite[0], true);
	output_individual(this->elite[0]);
}

size_t SLGP::Tournament(std::vector<Individual> pop, size_t tsize) {
	double code_max = 0;
	std::vector<size_t> candidate_idx_list = rnd.random_choice(this->pop_sample_idx, tsize);

	// code max
	for (size_t i = 0; i < tsize; i++) {
		code_max = std::max(code_max, (double)pop[candidate_idx_list[i]].code.size());
	}

	auto p_idx = candidate_idx_list[0];
	for (size_t i = 1; i < tsize; i++) {
		auto i_idx = candidate_idx_list[i];

		// code length penalty
		auto fitness_p_idx = pop[p_idx].fitness;
		auto fitness_i_idx = pop[i_idx].fitness;

		auto code_p_size = pop[p_idx].code.size();
		auto code_i_size = pop[i_idx].code.size();

#if(1)
		fitness_p_idx = fitness_p_idx * (code_p_size / code_max);
		fitness_i_idx = fitness_i_idx * (code_i_size / code_max);

		if (fitness_p_idx > fitness_i_idx) {
			p_idx = i_idx;
		}
#else
		if (fitness_p_idx >= fitness_i_idx) {
			p_idx = i_idx;
		}
		// same expression
		else if (fitness_p_idx == fitness_i_idx) {
			if (code_p_size > code_i_size) {
				p_idx = i_idx;
			}
		}
#endif

	}

	return p_idx;
}

// penalty?
void SLGP::ReGeneration(Individual& idv) {
#if(0)
	// regenration
	if ((idv.code.size() > this->NGenesMax) || (idv.code.size() < this->NGenesMin)) {
		auto gene_size = rnd((rand_type)this->NGenes, (rand_type)this->NGenesMax);
		idv.code.resize(gene_size);
		for (size_t i = 0; i < gene_size; i++) {
			SLGP_Code m_code;
			idv.code[i] = m_code;
		}
	}
#else
	// shrink
	if ((idv.code.size() > this->NGenesMax)) {
		idv.code.resize(this->NGenesMax);
	}
	else if ((idv.code.size() < this->NGenesMin)) {
		auto code_size = idv.code.size();
		idv.code.resize(this->NGenesMin);
		for (size_t i = code_size; i < this->NGenesMin; i++) {
			SLGP_Code m_code;
			idv.code[i] = m_code;
		}
	}
#endif
}

void SLGP::Summary(std::vector<Individual> pop) {
	vector<double> fitness_list;
	vector<double> code_length_list;

	fitness_list.reserve(this->pop.size());
	code_length_list.reserve(this->pop.size());
	for (size_t i = 0; i < this->pop.size(); i++) {
		fitness_list.emplace_back(pop[i].fitness);
		code_length_list.emplace_back((double)pop[i].code.size());
	}

	AggregateInfo agi_fitness(fitness_list);
	AggregateInfo agi_code_length(code_length_list);

	cout << "finetss info : " << endl << "\t";
	agi_fitness.ShowAggregate();

	cout << "code length info : " << endl << "\t";
	agi_code_length.ShowAggregate();
}

Individual SLGP::Mutate(Individual idv) {
	Individual idv_work = idv;
	auto m_id = rnd(0, (rand_type)(idv.code.size()-1));
	SLGP_Code m_code;
	idv_work.code[m_id] = m_code;
	return idv_work;
}

std::vector<Individual> SLGP::CrossOver(Individual parent1, Individual parent2) {
	std::vector<Individual> children(2);
	size_t cp1_start = rnd(parent1.code.size());
	size_t cp1_end = rnd(parent1.code.size());
	size_t cp2_start = rnd(parent2.code.size());
	size_t cp2_end = rnd(parent2.code.size());
	auto swap_cp = [&](size_t start, size_t end) { 
		if (start > end) {
			std::swap(start, end);
		}
	};

	swap_cp(cp1_start, cp1_end);
	swap_cp(cp2_start, cp2_end);

	// init children
	children[0] = parent1;
	children[0].code.clear();

	children[1] = parent2;
	children[1].code.clear();


	// build children
	for (size_t i = 0; i < cp1_start; i++) {
		children[0].code.push_back(parent1.code[i]);
	}
	for (size_t i = cp2_start; i < cp2_end; i++) {
		children[0].code.push_back(parent2.code[i]);
	}
	for (size_t i = cp1_end; i < parent1.code.size(); i++) {
		children[0].code.push_back(parent1.code[i]);
	}

	for (size_t i = 0; i < cp2_start; i++) {
		children[1].code.push_back(parent2.code[i]);
	}
	for (size_t i = cp1_start; i < cp1_end; i++) {
		children[1].code.push_back(parent1.code[i]);
	}
	for (size_t i = cp2_end; i < parent2.code.size(); i++) {
		children[1].code.push_back(parent2.code[i]);
	}

	return children;
}

void SLGP::SortPopulation(std::vector<Individual>& pop) {
	//auto ascending_order = [](const Individual& p, const Individual& q) { return (p.fitness < q.fitness); };
	//auto descending_order = [](const Individual& p, const Individual& q) { return (p.fitness > q.fitness); };
	auto better_order = [](const Individual& p, const Individual& q) { return better(p.fitness, q.fitness); };
	sort(pop.begin(), pop.end(), better_order);
}

std::vector<Individual> SLGP::SearchElite(std::vector<Individual>& pop) {
	SortPopulation(pop);
	std::vector<Individual> elite;
	elite.reserve(this->NElite);
	for (std::size_t i = 0; i < this->NElite; i++) {
		elite.emplace_back(pop[i]);
	}
	return elite;
}

void SLGP::output_individual(Individual idv) {
	std::string folder_name = ("./log/");
	std::string file_name = ("./elite_");
	std::string file_path;

	// timestamp
	time_t t = time(NULL);
	struct tm local;
	errno_t err = localtime_s(&local, &t);
	if (err == 0) {
		std::cerr << "failed local time" << endl;
	}
	auto time_stamp = std::put_time(&local, "%Y%m%d_%H%M%S");
	std::stringstream ss;
	ss << folder_name << file_name << time_stamp << ".csv";
	file_path = ss.str();

	std::error_code ec;
	bool result = std::filesystem::exists(folder_name, ec);
	if (result == false) {
		auto res = std::filesystem::create_directory(folder_name);
		if (res == false) {
			std::cerr << "fail mkdir" << endl;
		}
	}

	vector<reg_type> idv_output;
	this->problem->EvaluateIndividual(idv, idv_output);

	// make csv
	csv_parser::csv_data_type csv_data;
	csv_parser::word_list_type header;
	header.push_back("input");
	header.push_back("output");
	header.push_back("teach");
	csv_data.push_back(header);

	for (size_t i = 0; i < this->problem->problem_data.size(); i++) {
		csv_parser::word_list_type line;
		for (size_t j = 0; j < this->problem->problem_data[i].input.size(); j++) {
			line.push_back(std::to_string(this->problem->problem_data[i].input[j]));
		}

		// idv output (todo 2d output)
		//for (size_t j = 0; j < idv_output.size(); j++) {
		//	line.push_back(std::to_string(idv_output[j]));
		//}
		line.push_back(std::to_string(idv_output[i]));

		// teach
		for (size_t j = 0; j < this->problem->problem_data[i].output.size(); j++) {
			line.push_back(std::to_string(this->problem->problem_data[i].output[j]));
		}
		csv_data.push_back(line);
	}

	csv_parser::write_csv(file_path, csv_data, ",");
}

void SLGP::print_individual(Individual idv, bool print_code = false) {
	cout << "fitness = " << idv.fitness << endl;
	if (print_code == true) {
		cout << "--- code : ---------------" << endl;
		for (size_t i = 0; i < idv.code.size(); i++) {
			idv.code[i].PrintCode(idv.reg, false);
		}
	}
	cout << "--- output : ---------------" << endl;
	cout << idv.reg[this->problem->output_idx] << endl;
}

void SLGP::print_individual(size_t idx, bool print_code=false) {
	cout << "--- ID : " << idx << " ---------------" << endl;
	cout << "fitness = " << this->pop[idx].fitness << endl;
	if (print_code == true) {
		cout << "--- code : ---------------" << endl;
		for (size_t i = 0; i < this->pop[idx].code.size(); i++) {
			this->pop[idx].code[i].PrintCode(this->pop[idx].reg, false);
		}
	}
	cout << "--- output : ---------------" << endl;
	cout << this->pop[idx].reg[this->problem->output_idx] << endl;
}

void SLGP::print_individuals() {
	for (size_t i = 0; i < this->pop.size(); i++) {
		this->print_individual(i);
	}
}