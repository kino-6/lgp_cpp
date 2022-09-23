#include "SLGP_Problem.h"

void LoadProblem(std::string file_path){
	UNUSED(file_path);
}

void SLGP_Problem::LoadProblem_Stub(){
	// Stub sin data
	const unsigned int N_Data = 101;
	output_idx = 0;
	this->problem_data.resize(N_Data);

#if(1)	// sin
	for(unsigned int i=0; i<N_Data; i++) {
		reg_type x = -1 + 2.0/(N_Data-1)*i;
		this->problem_data[i].input.push_back(x);
		this->problem_data[i].output.push_back(std::sin(x*4) + (i*0.01));
	}
#else	// linear function
	for (unsigned int i = 0; i < N_Data; i++) {
		reg_type x = -5 + (i*0.1);
		this->problem_data[i].input.push_back(x);
		this->problem_data[i].output.push_back((i * 0.1) * 3 + 2);
	}

#endif
}

double SLGP_Problem::EvaluateIndividual(Individual idv, vector<reg_type>& output) {
	double error = 0;
	double fitness = 0;
	auto pow = [](double x) { return x * x; };
	output.reserve(this->problem_data.size());

	for (std::size_t i = 0; i < this->problem_data.size(); ++i) {
		// init register
		for (std::size_t i = 0; i < idv.reg.size(); ++i) {
			idv.reg[i] = 0;
		}

		// init register by input data
		for (std::size_t input_itr = 0; input_itr < this->problem_data[i].input.size(); ++input_itr) {
			idv.reg[input_itr] = this->problem_data[i].input[input_itr];
		}

		for (std::size_t j = 0; j < idv.code.size(); ++j) {
			idv.code[j].EvalCode(idv.reg);
		}

		for (std::size_t output_itr = 0; output_itr < this->problem_data[i].output.size(); ++output_itr) {
			output.emplace_back(idv.reg[output_itr]);
			error += pow(idv.reg[output_itr] - this->problem_data[i].output[output_itr]);
		}
	}

#if(0)	// 1 is good
	constexpr double C = 1.0;
	fitness = C / (error / this->problem_data.size() + C);
#else
	fitness = error;
#endif

	return fitness;
}

double SLGP_Problem::EvaluateIndividual(Individual idv){
	double error = 0;
	double fitness = 0;
	auto pow = [](double x){ return x*x; };

	for(std::size_t i = 0; i < this->problem_data.size(); ++i){
		// init register
		for (std::size_t i = 0; i < idv.reg.size(); ++i) {
			idv.reg[i] = 0;
		}

		// init register by input data
		for(std::size_t input_itr = 0; input_itr < this->problem_data[i].input.size(); ++input_itr){
			idv.reg[input_itr] = this->problem_data[i].input[input_itr];
		}

		for(std::size_t j = 0; j < idv.code.size(); ++j){
			idv.code[j].EvalCode(idv.reg);
		}

		for(std::size_t output_itr = 0; output_itr < this->problem_data[i].output.size(); ++output_itr){
			error += pow(idv.reg[output_itr] - this->problem_data[i].output[output_itr]);
		}
	}

#if(0)	// 1 is good
	constexpr double C=1.0;
	fitness = C/(error/this->problem_data.size()+C);
#else
	fitness = error;
#endif

	return fitness;
}

SLGP_Problem::SLGP_Problem(){
	// stub
	this->NRegisters = NREGISTERS;
	this->LoadProblem_Stub();
}

SLGP_Problem::~SLGP_Problem(void){
}