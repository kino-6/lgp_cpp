#ifndef SLGP_PROBLEM_H
#define SLGP_PROBLEM_H

#include "Common.h"
#include "SLGP_Common.h"
#include "csv_parser.hpp"

// 対象の問題について、管理・実行・評価する
class SLGP_Problem
{
	using RegisterType = double;
	typedef struct {
		std::vector<RegisterType> input;	// input[入力数]
		std::vector<RegisterType> output;
	} ProblemData;

	public:
		u64 NRegisters;
		std::vector<RegisterType> Register;				// レジスタセット

	private:
		CsvParser<RegisterType> cp;
		std::vector<ProblemData> problem_data;

	public:
		void LoadProblem(std::string file_path);
		void LoadProblem_Stub(std::string file_path);
		void InitProblem(void);
		void PrintProblem(void);
		double EvaluateIndividual(Individual idv);

		SLGP_Problem();
		SLGP_Problem(std::string file_path);
		~SLGP_Problem(void);
};

#endif	// SLGP_PROBLEM_H