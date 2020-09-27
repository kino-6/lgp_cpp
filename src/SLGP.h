#pragma once

#include <vector>
#include <random>
#include <iostream>
#include <string>

#include "SLGP_Problem.h"

// typedef unsigned char Code;
// typedef union {
// 	unsigned int gene;			/* 遺伝子(コード全体) */
// 	Code code[4];				/* 各コード */
// } Gene;

typedef unsigned int Gene;
typedef struct {
	std::vector<Gene> gene;		/* genes */
	double fitness;				/* fitness value */
} Individual;

template<typename T, std::size_t N> // see info
constexpr std::size_t arraySize(T(&)[N]) noexcept // below on
{ // constexpr
	return N; // and
}

class SLGP
{
	private:
		std::mt19937 mt;
		std::uniform_int_distribution<Gene> new_gene;
	public:
		SLGP_Problem problem;

		std::vector<Individual> pop;
		unsigned int Nvariables;	// 遺伝子の数
		unsigned int NOperators;	// 演算子の数
		unsigned int NRegisters;	// レジスターの数
		unsigned int NInputs;	// 入力変数の数
		unsigned int NConstants;	// 定数の数
		unsigned int NIndividuals;	// 個体の数

	public:
		SLGP(std::string problem_file);
		Gene MakeGene(unsigned int kind_of_genes);
		Individual MakeIndividual(unsigned int gene_num);
		void MakePopulation(unsigned int pop_size);
		void PrintIndividual(unsigned int idx);
		~SLGP();		
};