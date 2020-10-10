#include "SLGP_Code.h"
#include "WrapRamdom.hpp"

std::unordered_map<std::string , operator_set> OperatorMap= {
	{ "add", {"add", "+", 2 , SLGP_OperatorFunc::Add} },
	{ "sub", {"sub", "-", 2 , SLGP_OperatorFunc::Sub} },
	{ "mul", {"mul", "*", 2 , SLGP_OperatorFunc::Mul} },
	{ "div", {"div", "/", 2 , SLGP_OperatorFunc::Div} },
	{ "mod", {"mod", "%", 2 , SLGP_OperatorFunc::Mod} },
	{ "nop", {"nop", "%", 0 , SLGP_OperatorFunc::Nop} },
	{ "set", {"set", "=", 1 , SLGP_OperatorFunc::Set} },
};

SLGP_Code::SLGP_Code(){
	this->m_pHandlee = new SLGP_OperatorFunc();

	// mapからランダムにmap要素取得
	std::vector<std::string> v_keys;
	auto begin = OperatorMap.begin(), end = OperatorMap.end();
	for (auto iter = begin; iter != end; iter++) {
		v_keys.push_back(iter->first);
	}

	auto idx = rnd(0, v_keys.size()-1);

	GenerateCode( 	OperatorMap.at(v_keys[idx]).name,
					OperatorMap.at(v_keys[idx]).symbol,
					OperatorMap.at(v_keys[idx]).arity_num,
					OperatorMap.at(v_keys[idx]).Do
	);

	// 格納先レジスタ 0 - NREGISTERS のみ
	this->reg_num = rnd(0, (NREGISTERS-1));

	// ArityがRegister or Constかを決める
	auto reg_prob = (double)NREGISTERS / (double)(NREGISTERS + NCONSTANTS);
	rnd.randBool(reg_prob);
	
	// PrintCode();
}

void SLGP_Code::GenerateCode(std::string name, std::string symbol, u64 arity_num, func Do){
	this->name		= name;
	this->symbol	= symbol;
	
	this->arity.reserve(arity_num);
	for(std::size_t i=0; i<this->arity.capacity(); i++){
		this->arity.emplace_back(rnd(0,NCONSTANTS));
	}
	m_pHandlee->set_arity(this->arity);

	this->Do = Do;
}

void SLGP_Code::SetArity(std::vector<u64> arity){
	this->arity = arity;
	this->m_pHandlee->set_arity(this->arity);
}

u64 SLGP_Code::DoCode(){
	return (m_pHandlee->*Do)();
}

bool SLGP_Code::IsRegister(u64 idx){
	return this->arity.at(idx) > NCONSTANTS;
}

void SLGP_Code::PrintCode(){
	if( this->name == "nop" ){
		std::cout
			<< "nop"
			<< std::endl;
	}else if( this->name == "set" ){
		std::cout
			<< "r[" << this->reg_num << "] = "
			<< (i64)(m_pHandlee->*Do)() << " = "
			<< this->arity.at(0)
			<< std::endl;
	}else{
		std::cout
			<< "r[" << this->reg_num << "] = "
			<< (i64)(m_pHandlee->*Do)() << " = "
			<< this->arity.at(0)
			<< " " << this->symbol << " "
			<< this->arity.at(1)
			<< std::endl;
	}
}

SLGP_Code::~SLGP_Code(){

}