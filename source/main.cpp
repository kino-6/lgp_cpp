#include "std_lib.h"
#include "SLGP.h"

void filechk(std::string file);

int main(void){
	std::string file("data\\sin_data.csv");
	filechk(file);
	SLGP slgp(file);

	slgp.MakePopulation();	
	slgp.SearchBestIndividual(3);
	slgp.PrintIndividual(slgp.best, 0, true);

	return 0;
}

void filechk(std::string file){
	std::ifstream ifs(file, std::ios::in);

	std::cout << "file_path = " << file << std::endl;
	if (!ifs) {
		std::cout << "Error" << std::endl;
		std::exit(EXIT_FAILURE);
	}else{
		std::cout << "OK" << std::endl;
	}
}