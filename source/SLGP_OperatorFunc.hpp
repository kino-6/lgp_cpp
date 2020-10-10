#ifndef SLGP_OPErATORFUNC_H
#define SLGP_OPErATORFUNC_H

#include "Common.h"

class SLGP_OperatorFunc {
	private:
		std::vector<u64> arity;
	public: 
		void set_arity(std::vector<u64>& arity){
			this->arity = arity;
		}
	
		u64 Add(){
			return this->arity.at(0) + this->arity.at(1);
		}

		u64 Sub(){
			return this->arity.at(0) - this->arity.at(1);
		}

		u64 Mul(){
			return this->arity.at(0) * this->arity.at(1);
		}

		u64 Div(){
			if( this->arity.at(1) != 0 ){
				return this->arity.at(0) / this->arity.at(1);
			}else{
				return 0;
			}
		}

		u64 Mod(){
			if( this->arity.at(1) != 0 ){
				return this->arity.at(0) % this->arity.at(1);
			}else{
				return 0;
			}
		}

		u64 Nop(){
			return 0;
		}

		u64 Set(){
			return this->arity.at(0);
		}
};

#endif // SLGP_OPErATORFUNC_H