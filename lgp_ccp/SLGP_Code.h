#ifndef SLGP_CODE_H
#define SLGP_CODE_H

#include "Common.h"
#include "WrapRamdom.hpp"
#include "SLGP_OperatorFunc.hpp"

typedef reg_type (SLGP_OperatorFunc::*func)();

typedef struct{
	std::string name;
	std::string symbol;
	u64 arity_num;
	func Do;
} operator_set;

typedef enum {
	CODE_CONSTANTS,
	CODE_REGISTERS
} arity_e;

typedef struct {
	arity_e type;
	reg_type value;
} arity_t;

class SLGP_Code{
	private:
		void print_reg(std::vector<reg_type> reg);
		size_t get_reg_idx(arity_t arity);

	public:
		std::string name;
		std::string symbol;
		u64 arity_num;
		func Do;
		std::vector<arity_t> arity;
		u64 reg_num;
		SLGP_OperatorFunc* m_pHandlee;

	public:
		SLGP_Code();
		void SetArity(std::vector<arity_t> arity, std::vector<reg_type> reg);
		void print_arity(arity_t arity, std::vector<reg_type> reg);
		void GenerateCode(std::string name, std::string symbol, u64 arity_num, func Do);
		void PrintCode(std::vector<reg_type>& reg, bool print_reg_flag);
		void EvalCode(std::vector<reg_type>& reg);
		~SLGP_Code();
};

#endif // SLGP_CODE_H