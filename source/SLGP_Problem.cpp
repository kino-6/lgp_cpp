#include "SLGP_Problem.h"

void LoadProblem(std::string file_path){
	UNUSED(file_path);
#if(0)
	CsvParser<long double> cp;
	cp.ReadCsv(file_path, ',', 0, 0, "#");

	for(std::size_t i=0; i<cp.GetSize(); i++){
		if (i == 0) {
			std::cout << "\t" << std::ends;
		}
		else {
			std::cout << i << "\t" << std::ends;
		}

		for(std::size_t j=0; j<cp.GetSize(i); j++){
			if (i == 0) {
				
				std::cout << cp.GetLabels(i, j) << "\t" << std::ends;
			}
			else {
				std::cout << cp.GetData(i, j) << "\t" << std::ends;
			}
		}
		std::cout << std::endl;
	}
#endif
}

void SLGP_Problem::LoadProblem_Stub(std::string file_path){
	UNUSED(file_path);

	// Stub sin data
	unsigned int N_Data = 101;
	this->problem_data.resize(N_Data);
	
	for(unsigned int i=0; i<N_Data; i++) {
		RegisterType x=-5+10.0/(N_Data-1)*i;
		this->problem_data.at(i).input.push_back(x);
		this->problem_data.at(i).output.push_back(std::sin(x));
	}
}

// register[0]が出力になる（Stubの場合）
double SLGP_Problem::EvaluateIndividual(Individual idv){
	double error = 0;
	double fitness = 0;
	auto pow = [](double x){ return x*x; };

	// 問題データ数でループ
	for(std::size_t i = 0; i < this->problem_data.size(); ++i){
		// レジスターをInputで初期化
		for(std::size_t input_itr = 0; input_itr < this->problem_data.at(i).input.size(); ++input_itr){
			this->Register.at(input_itr) = this->problem_data.at(i).input.at(input_itr);
			// std::cout << "Register[" << input_itr << "] = " << this->Register.at(input_itr) << std::endl;
		}

		// 一つのInput[x] に対して、コード実行
		for(std::size_t j = 0; j < idv.code.size(); ++j){
			auto reg_idx = idv.code.at(j).reg_num;
			this->Register.at(reg_idx) = (RegisterType)(idv.code.at(j).DoCode());
			// idv.code.at(j).PrintCode();
			// std::cout << "Register[" << reg_idx << "] = " << this->Register.at(reg_idx) << std::endl;
		}

		for(std::size_t output_itr = 0; output_itr < this->problem_data.at(i).output.size(); ++output_itr){
			error += pow(this->Register.at(output_itr) - this->problem_data.at(i).output.at(output_itr));
		}
	}

	constexpr double C=1.0;
	fitness = C/(error/this->problem_data.size()+C);

	return fitness;
}

SLGP_Problem::SLGP_Problem(){
}

SLGP_Problem::SLGP_Problem(std::string file_path){
	UNUSED(file_path);
	// stub
	this->NRegisters = NREGISTERS;

	this->Register.resize(this->NRegisters);
	for(std::size_t i = 0; i < this->Register.size(); i++){
		this->Register.at(i) = 0;
	}

	this->LoadProblem_Stub(file_path);
}

SLGP_Problem::~SLGP_Problem(void){
}