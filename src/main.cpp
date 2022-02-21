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
	Forest forest;

	Tree tree(3);
	/*
	std::cout << tree.pft.name << "\n";

	std::cout << tree.diameter() << "\n";
	for (int year=0; year<200; year++) {
		tree.growth();
		std::cout << year << " "
			  << tree.diameter() << " "
			  << tree.height() << "\n";
	}
	*/

	return 0;
}
