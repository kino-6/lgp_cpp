#ifndef SLGP_H
#define SLGP_H

#include "Common.h"
#include "SLGP_Common.h"
#include "SLGP_Problem.h"

// SLGP統括 個体単位の操作をスコープとする
class SLGP
{
	public:
		u64 NVariables;		// 変数の数
		u64 NOperators;		// オペレータの数
		u64 NRegisters;		// レジスタの数
		u64 NInputs;		// Inputの数
		u64 NConstants;		// 定数の数
		u64 NIndividuals;	// 個体数
		u64 NGenes;			// 遺伝子数
		u64 NTimes;			// 世代数
		std::vector<Individual> pop;
		std::vector<Individual> best;

		SLGP_Problem problem;

	public:
		SLGP(std::string problem_file);
		SLGP_Code MakeGene();
		Individual MakeIndividual();

		void SearchBestIndividual(u64 best_size);

		void PrintIndividual(const std::vector<Individual>& pop, u64 idx, bool print_code);
		u64 MakePopulation();

		~SLGP();
};

#endif // SLGP_H