/********************************************************
 *							*
 *	MINIGAP - A forest simulator based on JABOWA	*
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

	//for (int p=0; p<npft(); p++) {
	//	Tree tree(p);
	//	for (int t=0; t<tree.pft.age_max; t++) {}
	//	std::cout << tree.pft.age_max << "\n";
	//}

	// Simulation of a single plot
	//Plot plot;
	//for (int i=0; i<500; i++) {
	//	plot.advance();
	//	increase_simulation_year();
	//}

	// Simulation of a forest (all plots are simultaneously maintained in memory)
	Forest forest(100);
	for (int year=0; year<500; year++) {
		forest.advance();
		increase_simulation_year();
	}

	return 0;
}
