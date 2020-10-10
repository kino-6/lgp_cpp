#include "SLGP_IO.h"

void SLGP_IO::output_csv(std::string out_filepath){
	std::ofstream out_stream;
	out_stream.open(out_filepath, std::ios::out);
}

SLGP_IO::SLGP_IO(){}
SLGP_IO::~SLGP_IO(){}
