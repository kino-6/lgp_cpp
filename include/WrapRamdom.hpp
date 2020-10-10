#pragma once
#include "std_lib.h"

// このクラスにランダム生成を押し付ける
// fast* 最速処理変数
class WrapRandom {
	using rand_type = std::uint_fast64_t;

private:
	std::mt19937_64 mt;
	std::random_device rd;

public:
	WrapRandom() { mt.seed(rd()); }

	void seed() {
		mt.seed(rd());
	}

	void seed(const rand_type seed) {
		mt.seed(seed);
	}	

	// return 64bit rand
	rand_type operator()() {
		return mt();
	}

	// (0,max)
	rand_type operator()(const rand_type max) {
		std::uniform_int_distribution<> uid(0, max);
		return uid(mt);
	}

	// (min, max)
	rand_type operator()(const rand_type min, const rand_type max) {
		std::uniform_int_distribution<> uid(min, max);
		return uid(mt);
	}

	// generate true by arg probability
	bool randBool(const double probability) {
		std::bernoulli_distribution uid(probability);
		return uid(mt);
	}

	// true or false
	bool randBool() {
		std::uniform_int_distribution<> uid(0, 1);
		return ((uid(mt)) ? true : false);
	}
};

// 遺伝子の初期化など、OpenMP活用を考慮（※プログラム終了時まで残留）
// static は明示的に付ける（暗黙で付くが）
static thread_local WrapRandom rnd;