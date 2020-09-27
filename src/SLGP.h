#pragma once

#include <vector>
#include <random>
#include <iostream>
#include <string>

#include "SLGP_Problem.h"

// typedef unsigned char Code;
// typedef union {
// 	unsigned int gene;			/* ��`�q(�R�[�h�S��) */
// 	Code code[4];				/* �e�R�[�h */
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
		unsigned int Nvariables;	// ��`�q�̐�
		unsigned int NOperators;	// ���Z�q�̐�
		unsigned int NRegisters;	// ���W�X�^�[�̐�
		unsigned int NInputs;	// ���͕ϐ��̐�
		unsigned int NConstants;	// �萔�̐�
		unsigned int NIndividuals;	// �̂̐�

	public:
		SLGP(std::string problem_file);
		Gene MakeGene(unsigned int kind_of_genes);
		Individual MakeIndividual(unsigned int gene_num);
		void MakePopulation(unsigned int pop_size);
		void PrintIndividual(unsigned int idx);
		~SLGP();		
};