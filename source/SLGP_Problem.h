#pragma once

#include "std_lib.h"

typedef long double ProblemType;
typedef struct {
	std::vector<ProblemType> input;
	std::vector<ProblemType> output;
} ProblemData;

typedef struct {
	std::string name;	// オペレーター名
	unsigned int arity;	// 引数の数
	char symbol;		// シンボル
} Operator;

typedef long double RegisterType;

enum class OperatorIdx:std::size_t { name, arity, symbol };

class SLGP_Problem
{
	private:
		std::vector<Operator> OPdefs;					// オペレータセット
		std::vector<RegisterType> Register;				// レジスタセット

		unsigned int NRegisters;						// Registerの数
		unsigned int NInputs;							// Inputの数
		unsigned int NConstants;						// [1,Nconstants]

	public:
		std::vector<ProblemData> problem_data;

	public:
		int LoadProblem(std::string file_path);
		void PrintOPdefs(void);
		void InitProblem(void);
		void PrintProblem(void);

		SLGP_Problem(void);
		SLGP_Problem(std::string file_path);
		~SLGP_Problem(void);
};