#include "SLGP.h"

SLGP::SLGP(std::string problem_file){
	this->pop.clear();

	// stub
	this->NVariables 	= 9;
	this->NOperators 	= 4;
	this->NRegisters 	= 9;
	this->NInputs    	= 3;
	this->NConstants 	= 2;
	this->NIndividuals 	= 20;
	this->NGenes		= 10;

	// problem_fileはProblemクラスへ投げる
	std::string path = problem_file;
	// Codeクラスへオペレータ生成委譲
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

	one.fitness = 0;

	return one;
}

void SLGP::PrintIndividual(u64 idx){
	std::cout << "--- idx = " << idx << " ------------------" << std::endl;
	for(std::size_t i=0; i<this->pop.at(idx).code.size(); i++){
		this->pop.at(idx).code.at(i).PrintCode();
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

SLGP::~SLGP(void){
	this->pop.clear();
}