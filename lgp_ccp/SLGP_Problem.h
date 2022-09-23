#ifndef SLGP_PROBLEM_H
#define SLGP_PROBLEM_H

#include "Common.h"
#include "SLGP_Common.h"

class SLGP_Problem
{
	typedef struct {
		std::vector<reg_type> input;
		std::vector<reg_type> output;
	} ProblemData;

	public:
		u64 NRegisters;
		size_t output_idx;
		std::vector<ProblemData> problem_data;

	public:
		//void LoadProblem(std::string file_path);
		void LoadProblem_Stub();
		//void InitProblem(void);
		//void PrintProblem(void);
		double EvaluateIndividual(Individual idv);
		double EvaluateIndividual(Individual idv, vector<reg_type>& output);

		SLGP_Problem();
		~SLGP_Problem(void);
};

#endif	// SLGP_PROBLEM_H