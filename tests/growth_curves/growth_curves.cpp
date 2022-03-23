#include <iostream>
#include "gap.h"

int main() {
	initialize_gap(); // Initialize model
	for (int p=0; p<npft(); p++) {
		Tree tree(p); // Create a tree of pft p
		std::cout << "* "
			  << tree.pft.name << " "
			  << tree.pft.d_max << " "
			  << tree.pft.h_max << " "
			  << tree.pft.age_max << "\n";
		for (int t=0; t<tree.pft.age_max + 1 + 5; t++) {
			std::cout << t << " " << tree.diameter() << " "
					      << tree.height() << " "
					      << tree.weight() << " "
					      << tree.basal_area() << " "
					      << "\n";
			tree.growth();
		}
	}
	return 0;
}
