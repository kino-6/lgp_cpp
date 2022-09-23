#ifndef SLGP_COMMON
#define SLGP_COMMON

#include "std_lib.h"
#include "Common.h"
#include "SLGP_Code.h"

typedef struct {
	std::vector<SLGP_Code> code;	/* code */
	std::vector<reg_type> reg;		/* registers */
	double fitness;					/* fitness value */
} Individual;

#endif // SLGP_COMMON