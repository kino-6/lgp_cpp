#pragma once

#include "std_lib.h"
#include "SLGP_Problem.h"

// typedef unsigned char Code;
// typedef union {
// 	unsigned int gene;			/* genes */
// 	Code code[4];				/* geneのchar読み替え */
// } Gene;

typedef unsigned int Gene;
typedef struct {
	std::vector<Gene> gene;		/* genes */
	double fitness;				/* fitness value */
} Individual;

template<typename T, std::size_t N>
constexpr std::size_t arraySize(T(&)[N]) noexcept
{ return N; }

class SLGP
{
	private:
		std::mt19937 mt;
		std::uniform_int_distribution<Gene> new_gene;
	public:
		SLGP_Problem problem;

		std::vector<Individual> pop;
		unsigned int Nvariables;	// 変数の数
		unsigned int NOperators;	// オペレータの数
		unsigned int NRegisters;	// レジスタの数
		unsigned int NInputs;		// Inputの数
		unsigned int NConstants;	// 定数の数
		unsigned int NIndividuals;	// 個体数

	public:
		SLGP(std::string problem_file);
		Gene MakeGene(unsigned int kind_of_genes);
		Individual MakeIndividual(unsigned int gene_num);
		void MakePopulation(unsigned int pop_size);
		void PrintIndividual(unsigned int idx);
		~SLGP();		
};