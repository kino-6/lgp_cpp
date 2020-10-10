#ifndef SLGP_CODE_H
#define SLGP_CODE_H

#include "Common.h"
#include "WrapRamdom.hpp"
#include "SLGP_OperatorFunc.hpp"

typedef u64 (SLGP_OperatorFunc::*func)();

typedef struct{
	std::string name;
	std::string symbol;
	u64 arity_num;
	func Do;
} operator_set;

// code単体のクラス定義
class SLGP_Code{
	public:
		std::string name;
		std::string symbol;
		u64 arity_num;
		func Do;
		std::vector<u64> arity;
		u64 reg_num;
		bool is_register;

		SLGP_OperatorFunc* m_pHandlee;

	public:
		SLGP_Code();
		bool IsRegister(u64 idx);
		void SetArity(std::vector<u64> arity);
		u64 DoCode();
		void GenerateCode(std::string name, std::string symbol, u64 arity_num, func Do);
		void PrintCode();
		~SLGP_Code();
};

#endif // SLGP_CODE_H