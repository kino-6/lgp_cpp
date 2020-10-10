#pragma once
#include "Common.h"
#include "SLGP_Code.h"

// SLGP統括 個体単位の操作をスコープとする

// 個体定義
typedef struct {
	std::vector<SLGP_Code> code;	/* code */
	double fitness;					/* fitness value */
} Individual;

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
		std::vector<Individual> pop;

	public:
		SLGP(std::string problem_file);
		SLGP_Code MakeGene();
		Individual MakeIndividual();
		void PrintIndividual(u64 idx);
		u64 MakePopulation();

		~SLGP();
};