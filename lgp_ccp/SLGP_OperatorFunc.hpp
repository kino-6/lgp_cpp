#ifndef SLGP_OPERATORFUNC_H
#define SLGP_OPERATORFUNC_H

#include "Common.h"

class SLGP_OperatorFunc {
	private:
		std::vector<reg_type> arity;
	public: 
		void set_arity(std::vector<reg_type>& arity){
			this->arity = arity;
		}
	
		reg_type Add(){
			return this->arity[0] + this->arity[1];
		}

		reg_type Sub(){
			return this->arity[0] - this->arity[1];
		}

		reg_type Mul(){
			return this->arity[0] * this->arity[1];
		}

		reg_type Div(){
			if( this->arity[1] != 0 ){
				return this->arity[0] / this->arity[1];
			}else{
				return 0;
			}
		}

		reg_type Mod(){
			if( this->arity[1] != 0 ){
				return std::fmod(this->arity[0], this->arity[1]);
			}else{
				return 0;
			}
		}

		reg_type Nop(){
			return 0;
		}

		reg_type Set(){
			return this->arity[0];
		}
};

#endif // SLGP_OPERATORFUNC_H