#include "SLGP_Code.h"
#include "WrapRamdom.hpp"

std::unordered_map<std::string , operator_set> OperatorMap = {
	{ "add", {"add", "+", 2 , &SLGP_OperatorFunc::Add} },
	{ "sub", {"sub", "-", 2 , &SLGP_OperatorFunc::Sub} },
	{ "mul", {"mul", "*", 2 , &SLGP_OperatorFunc::Mul} },
	{ "div", {"div", "/", 2 , &SLGP_OperatorFunc::Div} },
	{ "mod", {"mod", "%", 2 , &SLGP_OperatorFunc::Mod} },
	{ "nop", {"nop", "%", 0 , &SLGP_OperatorFunc::Nop} },
	{ "set", {"set", "=", 1 , &SLGP_OperatorFunc::Set} },
};

SLGP_Code::SLGP_Code(){
	this->m_pHandlee = new SLGP_OperatorFunc();

	std::vector<std::string> v_keys;
	v_keys.reserve(OperatorMap.size());
	auto begin = OperatorMap.begin(), end = OperatorMap.end();
	for (auto iter = begin; iter != end; iter++) {
		v_keys.emplace_back(iter->first);
	}

	auto idx = rnd(0, (rand_type)(v_keys.size()-1));

	GenerateCode( 	OperatorMap.at(v_keys[idx]).name,
					OperatorMap.at(v_keys[idx]).symbol,
					OperatorMap.at(v_keys[idx]).arity_num,
					OperatorMap.at(v_keys[idx]).Do
	);

	this->reg_num = rnd(0, (rand_type)(NREGISTERS-1));
}

void SLGP_Code::GenerateCode(std::string name, std::string symbol, u64 arity_num, func Do){
	this->name		= name;
	this->symbol	= symbol;
	
	this->arity.reserve(arity_num);
	for (std::size_t i = 0; i < this->arity.capacity(); i++) {
		// arity is register or constants
		if (rnd.randBool() == true) {
			// constants
			this->arity.push_back({ CODE_CONSTANTS, rnd(0.0, NCONSTANTS) });
		}
		else {
			// register, reg_idx get from truncated value.
			this->arity.push_back({ CODE_REGISTERS, rnd(0.0, (NREGISTERS - 1)) });
		}
	}

	this->Do = Do;
}

size_t SLGP_Code::get_reg_idx(arity_t arity) {
	return (size_t)std::trunc(arity.value);
}

void SLGP_Code::SetArity(std::vector<arity_t> arity, std::vector<reg_type> reg){
	vector<reg_type> arity_work;

	arity_work.reserve(arity.size());
	for (size_t i = 0; i < arity.size(); i++) {
		if ( arity[i].type == CODE_REGISTERS ) {
			arity_work.emplace_back( reg[get_reg_idx(arity[i])] );
		}
		else {
			arity_work.emplace_back(arity[i].value);
		}
	}

	this->m_pHandlee->set_arity(arity_work);
}

void SLGP_Code::EvalCode(std::vector<reg_type>& reg) {
	this->SetArity(this->arity, reg);
	reg[this->reg_num] = (reg_type)(m_pHandlee->*Do)();
}

void SLGP_Code::print_reg(std::vector<reg_type> reg) {
	for (size_t i = 0; i < reg.size(); i++) {
		cout << reg[i] << " ";
	}
}

void SLGP_Code::print_arity(arity_t arity, std::vector<reg_type> reg) {
	if ( arity.type == CODE_REGISTERS ) {
		cout << "r[" << get_reg_idx(arity) << "] ";
	}
	else {
		cout << arity.value;
	}
}

void SLGP_Code::PrintCode(std::vector<reg_type>& reg, bool print_reg_flag=false) {
	// eval
	this->EvalCode(reg);

	// print
	if (this->name == "nop") {
		std::cout
			<< "nop";
			cout << std::endl;
	}
	else if (this->name == "set") {
		std::cout
			<< "r[" << this->reg_num << "] = "
			<< (reg_type)(m_pHandlee->*Do)() << " = ";
			print_arity(this->arity[0], reg);
			cout << "\t\t";
			if (print_reg_flag == true) {
				print_reg(reg);
			}
			cout << std::endl;
	}
	else {
		std::cout
			<< "r[" << this->reg_num << "] = "
			<< (reg_type)(m_pHandlee->*Do)() << " = ";
			print_arity(this->arity[0], reg);
			cout << " " << this->symbol << " ";
			print_arity(this->arity[1], reg);
			cout << "\t";
			if (print_reg_flag == true) {
				print_reg(reg);
			}
			cout << std::endl;
	}
}

SLGP_Code::~SLGP_Code(){

}