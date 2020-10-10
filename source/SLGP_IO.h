#pragma once

#include "std_lib.h"
#include "SLGP.h"

// I/O関連

class SLGP_IO
{

public:
	void output_csv(std::string out_filepath);

	SLGP_IO();
	~SLGP_IO();
};