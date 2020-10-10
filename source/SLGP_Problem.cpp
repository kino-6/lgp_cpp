#include "SLGP_Problem.h"

std::vector<Operator> DefaultOPdefs={
	{"add", 2, '+'},
	{"sub", 2, '-'},
	{"mul", 2, '*'},
	{"div", 2, '/'},
	{"nop", 0, 'n'},
};

SLGP_Problem::SLGP_Problem(void){
}

SLGP_Problem::SLGP_Problem(std::string file_path){
	this->LoadProblem(file_path);

	// stub
	this->NRegisters = 4;
	this->NInputs = 0;
	this->NConstants = 9;

	for(std::size_t i = 0; i < DefaultOPdefs.size(); i++){
		this->OPdefs.push_back( DefaultOPdefs.at(i) );
	}

	this->Register.resize(this->NRegisters);
	for(std::size_t i = 0; i < this->Register.size(); i++){
		this->Register.at(i) = 0;
	}

	this->InitProblem();
}

void SLGP_Problem::PrintOPdefs(void){
	for(std::size_t i = 0; i < this->OPdefs.size(); i++){
		std::cout
			<< "name =		"	<< this->OPdefs.at(i).name		<< "\n"
			<< "arity =		"	<< this->OPdefs.at(i).arity		<< "\n"
			<< "symbol =	"	<< this->OPdefs.at(i).symbol	<< "\n"
			<< std::endl;
	}
}

int SLGP_Problem::LoadProblem(std::string file_path){
	return 0;
}

void SLGP_Problem::InitProblem(void){
	// load problem from file

	// Stub sin data
	unsigned int N_Data = 101;
	this->problem_data.resize(N_Data);
	
	for(unsigned int i=0; i<N_Data; i++) {
		ProblemType x=-5+10.0/(N_Data-1)*i;
		this->problem_data.at(i).input.push_back(x);
		this->problem_data.at(i).output.push_back(std::sin(x));
	}
}

void SLGP_Problem::PrintProblem(void){
	for(std::size_t i = 0; i < this->problem_data.size(); i++){
		std::cout
			<< "input =		"	<< this->problem_data.at(i).input[0]		<< "\n"
			<< "output =	"	<< this->problem_data.at(i).output[0]		<< "\n"
			<< std::endl;
	}
}

//���Z�q�̈�����]��
// void SLGP_Problem::EvalCode(std::vector<Gene> code, std::vector<ProblemType> arg)
// {
// 	for (auto it = std::begin(code); it != std::end(code); ++it) {
// 		//auto arity = this->OPdefs.at(*it);	// gene��opdef��idx
// 	}
// }


// Register[:] �����ׂ�Input�Ŗ��߂�A�����Input�̐��������{����
// Register[:] = Input[x]
// Output[x] = RunProgram(Register[:])
// void SLGP_Problem::RunProgram(std::vector<Gene> gene){
// 	auto arity = gene;
// 	std::vector<ProblemType> arg;
// }

SLGP_Problem::~SLGP_Problem(void){
}