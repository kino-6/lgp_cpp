#include "SLGP.h"

SLGP::SLGP(std::string problem_file){
	this->pop.clear();

	// stub
	this->NVariables 	= 9;
	this->NOperators 	= 4;
	this->NRegisters 	= 9;
	this->NInputs    	= 3;
	this->NConstants 	= 2;
	this->NIndividuals 	= 10;
	this->NGenes		= 30;
	this->NTimes		= 200;

	// problem_fileはProblemクラスへ投げる
	this->problem = SLGP_Problem(problem_file);
}

// 遺伝子生成
SLGP_Code SLGP::MakeGene(){
	return SLGP_Code();
}

// 個体生成
Individual SLGP::MakeIndividual(){
	Individual one;
	one.code.reserve(this->NGenes);

	for(std::size_t i=0; i<one.code.capacity(); i++){
		one.code.emplace_back();	// reserve + emplace_backでコピーコンストラクタを避ける
	}

	one.fitness = this->problem.EvaluateIndividual(one);

	return one;
}

void SLGP::PrintIndividual(const std::vector<Individual>& pop, u64 idx, bool print_code){
	if( print_code ){
		std::cout << "--- idx = " << idx << " ------------------" << std::endl;
		for(std::size_t i=0; i<this->pop.at(idx).code.size(); i++){
			this->pop.at(idx).code.at(i).PrintCode();
		}
		std::cout << "fitness = " << pop.at(idx).fitness << std::endl;
	}else{
		std::cout << idx << " : fitness = " << pop.at(idx).fitness << std::endl;
	}
}

// 集団生成
u64 SLGP::MakePopulation(){
	u64 best_idx = 0;

	this->pop.reserve(this->NIndividuals);
	for(std::size_t i=0; i<this->NIndividuals; i++){
		this->pop.emplace_back(MakeIndividual());
	}

	return best_idx;
}

// ベスト個体のサーチと確保
void SLGP::SearchBestIndividual(u64 best_size){
	// auto ascending_order	= [](const Individual& p, const Individual& q){ return (p.fitness < q.fitness); };
	auto descending_order	= [](const Individual& p, const Individual& q){ return (p.fitness > q.fitness); };
	sort(this->pop.begin(), this->pop.end(), descending_order);
	
	this->best.reserve(best_size);
	for(std::size_t i=0; i<this->best.capacity(); i++){
		this->best.emplace_back(this->pop.at(i));
	}
}

SLGP::~SLGP(void){
	this->pop.clear();
}