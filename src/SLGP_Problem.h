#pragma once

// オペコードの解決
// xml から問題のシリアライズ

#include <string>
#include <vector>
#include <iostream>
#include <cmath>

typedef long double ProblemType;
typedef struct {
	std::vector<ProblemType> input;
	std::vector<ProblemType> output;
} ProblemData;

typedef struct {
	std::string name;	// 演算子名
	unsigned int arity;	// 引数の数
	char symbol;		// 演算子のニモニック
} Operator;

typedef long double RegisterType;

enum class OperatorIdx:std::size_t { name, arity, symbol };

class SLGP_Problem
{
	private:
		std::vector<Operator> OPdefs;					// オペレータセット
		std::vector<RegisterType> Register;				// レジスタ

		unsigned int NRegisters;						// レジスター数
		//unsigned int NInputs=N_INPUTS;				// 入力変数を直接使用する場合
		unsigned int NInputs;							// 入力変数を使用せず，入力レジスタを使用する場合
		unsigned int NConstants;						// 定数の数([1,Nconstants]間の整数)

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