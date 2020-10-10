#ifndef SLGP_COMMON
#define SLGP_COMMON

#include "std_lib.h"
#include "SLGP_Code.h"

// 個体定義
typedef struct {
	std::vector<SLGP_Code> code;	/* code */
	double fitness;					/* fitness value */
} Individual;

#endif // SLGP_COMMON