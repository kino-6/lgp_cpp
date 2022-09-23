#pragma once
#include "SLGP_Common.h"
#include "SLGP_Problem.h"

class SLGP
{
public:
	u64 NVariables;			// �ϐ��̐�
	u64 NOperators;			// �I�y���[�^�̐�
	u64 NRegisters;			// ���W�X�^�̐�
	u64 NInputs;			// Input�̐�
	u64 NConstants;			// �萔�̐�
	u64 NIndividuals;		// �̐�
	u64 NElite;				// Elite��
	u64 NGenes;				// ��`�q��
	u64 NGenesMin;			// ��`�q�ŏ���
	u64 NGenesMax;			// ��`�q�ő吔
	u64 NTimes;				// ���㐔
	size_t tsize;			// �g�[�i�����g�T�C�Y

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

