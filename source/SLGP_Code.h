#pragma once
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
// CodeFactoryで生成
class SLGP_Code{
	public:
		std::string name;
		std::string symbol;
		u64 arity_num;
		func Do;

	private:
		std::vector<u64> arity;

	public:
		void set_arity(std::vector<u64>& arity);

	public:
		SLGP_Code();
		void GenerateCode(std::string name, std::string symbol, u64 arity_num, func Do);
		void PrintCode();
		~SLGP_Code();
};