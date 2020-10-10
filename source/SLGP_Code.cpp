#include "SLGP_Code.h"
#include "WrapRamdom.hpp"

std::unordered_map<std::string , operator_set> OperatorMap= {
	{ "add", {"add", "+", 2 , SLGP_OperatorFunc::Add} },
	{ "sub", {"sub", "-", 2 , SLGP_OperatorFunc::Sub} },
	{ "mul", {"mul", "*", 2 , SLGP_OperatorFunc::Mul} },
	{ "div", {"div", "/", 2 , SLGP_OperatorFunc::Div} },
	{ "mod", {"mod", "%", 2 , SLGP_OperatorFunc::Mod} },
	{ "nop", {"nop", "%", 0 , SLGP_OperatorFunc::Nop} },
};

SLGP_Code::SLGP_Code(){
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
	// PrintCode();
}

void SLGP_Code::GenerateCode(std::string name, std::string symbol, u64 arity_num, func Do){
	this->name		= name;
	this->symbol	= symbol;
	
	this->arity.reserve(arity_num);
	for(std::size_t i=0; i<this->arity.capacity(); i++){
		this->arity.emplace_back(rnd(0,9));
	}

	this->Do = Do;
}

void SLGP_Code::PrintCode(){
	if( this->name != "nop" ){
		std::cout
			<< "result = "
			<< this->arity.at(0)
			<< " " << this->symbol << " "
			<< this->arity.at(1)
			<< std::endl;
	}else{
		std::cout
			<< "nop"
			<< std::endl;
	}
}

SLGP_Code::~SLGP_Code(){

}