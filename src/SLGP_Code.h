#pragma once

#include "SLGP.h"
#include "SLGP_Problem.h"

// �I�y�R�[�h�̎��s�Q

template<typename T>
class SLGP_Code{
	private:
		std::vector<T> reg;

	public:
		SLGP_Code(void);
		T operator*(const T& t1, const T& t2, const T& reg_idx) { reg.at(reg_idx) = T(t1) * T(t2); }
		T operator/(const T& t1, const T& t2) { return T(t1) /= t2; }
		T operator%(const T& t1, const T& t2) { return T(t1) %= t2; }
		T operator+(const T& t1, const T& t2) { return T(t1) += t2; }
		T operator-(const T& t1, const T& t2) { return T(t1) -= t2; }
};