/************************************************************
 *							    *
 *      MINIGAP - A forest simulator based on JABOWA v1	    *
 *		Botkin, Janak and Wallis (1972)		    *
 *		https://doi.org/10.2307/2258570		    *
 *							    *
 ************************************************************/

#include <iostream>
#include "gap.h"

int main() {

	// Initialize model
	initialize_gap();

	// Simulation of a single plot
	// (A forest could be simulated one plot at a time)
	//Plot plot;
	//for (int i=0; i<500; i++) {
	//	plot.advance();
	//	std::cout << plot.info() << "\n";
	//	increase_simulation_year();
	//}

	// Simulation of a forest in which all plots are
	// simultaneously maintained in memory.
	Forest forest(100);
	std::cout << get_header() << "\n";
	for (int year=0; year<500; year++) {
		forest.advance();
		forest.dump_output();
		increase_simulation_year();
	}

	return 0;
}
