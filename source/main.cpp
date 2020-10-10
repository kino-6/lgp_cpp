#include <iostream>
#include "SLGP.h"

int main(void){
	SLGP slgp("hoge");
	slgp.MakePopulation(10);
	// slgp.PrintIndividual(0);

	slgp.problem.PrintOPdefs();
	slgp.problem.PrintProblem();

	return 0;
}