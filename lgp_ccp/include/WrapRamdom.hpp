#ifndef WRAPRAMDOM_H
#define WRAPRAMDOM_H

#include "std_lib.h"

class WrapRandom {
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

	// return 32bit rand
	rand_type operator()() {
		return (rand_type)mt();
	}

	// (0,max)
	rand_type operator()(const rand_type max) {
		std::uniform_int_distribution<> uid((rand_type)0, max);
		return uid(mt);
	}

	// (0,max)
	size_t operator()(const size_t max) {
		std::uniform_int_distribution<> uid((rand_type)0, (rand_type)max);
		return (size_t)uid(mt);
	}

	// (min, max)
	rand_type operator()(const rand_type min, const rand_type max) {
		std::uniform_int_distribution<> uid(min, max);
		return uid(mt);
	}

	// (min, max)
	size_t operator()(const size_t min, const size_t max) {
		std::uniform_int_distribution<> uid((rand_type)min, (rand_type)max);
		return (size_t)uid(mt);
	}

	// (min, max)
	double operator()(const double min, const double max) {
		std::uniform_real_distribution<> uid(min, max);
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

	std::vector<size_t> random_choice(std::vector<size_t> lst, size_t n) {
		std::shuffle(lst.begin(), lst.end(), mt);
		
		std::vector<size_t> res;
		for (size_t i = 0; i < n; i++) {
			res.push_back(lst[i]);
		}

		return res;
	}

};

static thread_local WrapRandom rnd;

#endif // WRAPRAMDOM_H