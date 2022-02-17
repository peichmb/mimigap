#include <vector>
#include "gap.h"

namespace {
	// List with all the static PFT parameters
	std::vector<Pft> pft_list;
}


// --------------------//
// 	class Tree     //
// --------------------//

Tree::Tree (int pft_id) {
	h = 0.;
	d = 0.;
}

void Tree::growth() {

	Pft& pft = pft_list[pft_id];

	// Calculate change in tree diameter over 1 year (B79, Eq. 5)
	double d_change = pft.g*d*(1.-d*h/(pft.d_max * pft.h_max))
			/ (2.74 + 3.*pft.b2*d - 4.*pft.b3*d*d);
	// Update diameter
	d = d + d_change;
}

Tree::~Tree() {}


// ---------------------//
// 	class Stand     //
// ---------------------//

Stand::Stand() {}
Stand::~Stand() {}
