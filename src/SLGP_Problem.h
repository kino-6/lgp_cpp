#pragma once

// �I�y�R�[�h�̉���
// xml ������̃V���A���C�Y

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
	std::string name;	// ���Z�q��
	unsigned int arity;	// �����̐�
	char symbol;		// ���Z�q�̃j���j�b�N
} Operator;

typedef long double RegisterType;

enum class OperatorIdx:std::size_t { name, arity, symbol };

class SLGP_Problem
{
	private:
		std::vector<Operator> OPdefs;					// �I�y���[�^�Z�b�g
		std::vector<RegisterType> Register;				// ���W�X�^

		unsigned int NRegisters;						// ���W�X�^�[��
		//unsigned int NInputs=N_INPUTS;				// ���͕ϐ��𒼐ڎg�p����ꍇ
		unsigned int NInputs;							// ���͕ϐ����g�p�����C���̓��W�X�^���g�p����ꍇ
		unsigned int NConstants;						// �萔�̐�([1,Nconstants]�Ԃ̐���)

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