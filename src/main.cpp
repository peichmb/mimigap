/********************************************************
 *							*
 *	MINIGAP - A mini-sized forest simulator		*
 *	Based on JABOWA (Botkin et. al, 1972)		*
 *	https://doi.org/10.2307/2258570			*
 *							*
 ********************************************************/

#include <iostream>
#include "gap.h"

int main() {

	// Initialize model
	initialize_gap();

	// Create forest object
	//Forest forest;

	for (int p=0; p<13; p++) {
		Tree tree(p);
		for (int t=0; t < tree.pft.age_max; t++) {}
		std::cout << tree.pft.age_max << "\n";
	}

	return 0;
}
