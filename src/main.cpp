/********************************************************
 *							*
 *	MINIGAP - A C++ implementation of JABOWA v1	*
 *	Botkin, Janak and Wallis (1972)			*
 *	https://doi.org/10.2307/2258570			*
 *							*
 *							*
 ********************************************************/

#include <iostream>
#include "gap.h"

int main() {

	// Initialize model
	initialize_gap();

	// Create forest object
	//Forest forest;

	for (int p=0; p<npft(); p++) {
		Tree tree(p);
		for (int t=0; t<tree.pft.age_max; t++) {}
		std::cout << tree.pft.age_max << "\n";
	}

	return 0;
}
