#include <iostream>
#include "SLGP.h"

int main(void){
	SLGP slgp("hoge");

	slgp.NIndividuals = 20;
	slgp.MakePopulation();
	
	slgp.PrintIndividual(0);

	return 0;
}