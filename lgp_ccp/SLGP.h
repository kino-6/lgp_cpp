#pragma once
#include "SLGP_Common.h"
#include "SLGP_Problem.h"

class SLGP
{
public:
	u64 NVariables;			// 変数の数
	u64 NOperators;			// オペレータの数
	u64 NRegisters;			// レジスタの数
	u64 NInputs;			// Inputの数
	u64 NConstants;			// 定数の数
	u64 NIndividuals;		// 個体数
	u64 NElite;				// Elite数
	u64 NGenes;				// 遺伝子数
	u64 NGenesMin;			// 遺伝子最小数
	u64 NGenesMax;			// 遺伝子最大数
	u64 NTimes;				// 世代数
	size_t tsize;			// トーナメントサイズ

	double PMutate;
	double PCrossOver;

	std::vector<Individual> pop;
	std::vector<Individual> new_pop;
	std::vector<Individual> elite;
	SLGP_Problem* problem;
	std::vector<size_t> pop_sample_idx;

	SLGP();
	~SLGP();

	void SLGP_Main();
	size_t Tournament(std::vector<Individual> pop, size_t tsize);
	Individual Mutate(Individual idv);
	std::vector<Individual> CrossOver(Individual parent1, Individual parent2);
	void SortPopulation(std::vector<Individual>& pop);
	std::vector<Individual> SearchElite(std::vector<Individual>& pop);
	void ReGeneration(Individual& idv);

	void Summary(std::vector<Individual> pop);
	void output_individual(Individual idv);
	void print_individual(size_t idx, bool print_code);
	void print_individual(Individual idv, bool print_code);
	void print_individuals();
};

