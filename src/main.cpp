/************************************************************
 *							    *
 *      MINIGAP - A forest simulator based on JABOWA v1	    *
 *		Botkin, Janak and Wallis (1972)		    *
 *		https://doi.org/10.2307/2258570		    *
 *							    *
 ************************************************************/

#include <iostream>
#include "gap.h"

typedef enum {SINGLE_PLOT, FOREST} simulation_type;

void simulate_single_plot(int nyears);

void simulate_forest(int nyears, int nplots);

int main() {

	// Parameters
	const int nyears = 500;
	const simulation_type sim_type = FOREST;
	const int nplots_forest = 100;

	// Initialize model
	initialize_gap();

	switch (sim_type) {
	case SINGLE_PLOT:
		simulate_single_plot(nyears);
		break;
	case FOREST:
		simulate_forest(nyears, nplots_forest);
		break;
	default:
		std::cout << "Unknown simulation type";
		return 1;
	}

	return 0;
}

// Simulation of a single plot
// (A forest could be simulated one plot at a time)
void simulate_single_plot(int nyears) {
	// Create plot
	Plot plot;
	for (int i=0; i<nyears; i++) {
		// Simulate one year
		plot.advance();
		// Print out info
		std::cout << plot.info() << "\n";
		// Increase simulation year counter
		increase_simulation_year();
	}
}


// Simulation of a forest in which all plots are
// simultaneously maintained in memory.
void simulate_forest(int nyears, int nplots) {
	// Create forest object with nplots plots
	Forest forest(nplots);
	// Print out header
	std::cout << get_header() << "\n";
	// Main loop
	for (int year=0; year<nyears; year++) {
		// Simulate one year
		forest.advance();
		// Print out plots info
		forest.dump_output();
		// Increase simulation year counter
		increase_simulation_year();
	}
}

