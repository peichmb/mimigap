#include <vector>
#include <math.h>
#include "gap.h"
#include <iostream>

namespace {

	const double DIAMETER_MIN = 0.5;
	// Vector containing the static PFT parameters
	std::vector<Pft> pft_list;
	// Vector of ids of shade tolerant/intolerant PFTs
	std::vector<int> shade_tolerant_pfts;
	std::vector<int> shade_intolerant_pfts;
}


// --------------------//
// 	class Tree     //
// --------------------//

Tree::Tree (int pft_id) : pft(pft_list[pft_id]), pft_id(pft_id) {
	// WORKSHOP: Initialize these to zero to let them catch the bug.
	d = DIAMETER_MIN;
	update_height();
}

void Tree::growth() {

	// Calculate change in tree diameter over 1 year (B79, Eq. 5)
	double d_change = pft.g*d*(1.-d*h/(pft.d_max * pft.h_max))
			/ (274 + 3.*pft.b2*d - 4.*pft.b3*d*d);
	/*
	std::cout << d_change << "\n";
	std::cin.ignore();
	*/
	// Environmental factors affecting growth
	double f_env = 1.;
	// Update diameter
	d = d + d_change*f_env;
	// Update height
	update_height();
}

double Tree::diameter() { return d; }

double Tree::height() { return h; }

void Tree::update_height() { h = 137 + pft.b2*d - pft.b3*d*d; }

double Tree::r_light(double al) {

	if (pft.type == SHADE_TOLERANT) {
		return 1. - exp(-4.64*(al-0.05));
	} else {
		return 2.24*(1. - exp(-1.136*(al-0.08)));
	}
}

Tree::~Tree() {}


// ---------------------//
// 	class Stand     //
// ---------------------//

//Stand::Stand(Forest& parent_forest) : forest(parent_forest) {}
Stand::Stand() {}
Stand::~Stand() {}


// ---------------------//
// 	class Forest     //
// ---------------------//

Forest::Forest() {}
Forest::~Forest() {}


// ---------------------------- //
// 	module functions	//
// ---------------------------- //

void initialize_gap() {
	// Populate pft list
	// Parameters from Botkin et al. (1972)
	//
	// 				Name        g      c  age_max              type  d_max  h_max    b2     b3 dgde_min dgde_max  wmin  wmax
	pft_list.push_back(Pft {"Sugar maple",   170., 1.57 ,     200,   SHADE_TOLERANT, 152.5, 4011., 50.9, 0.167,   2000.,   6300., 300.,  -1.});
	pft_list.push_back(Pft {"Beech", 	 150., 2.20 ,     300,   SHADE_TOLERANT, 122.0, 3660., 57.8, 0.237,   2100.,   6000., 300.,  -1.});
	pft_list.push_back(Pft {"Yellow birch",  100., 0.486,     300, SHADE_INTOLERANT, 122.0, 3050., 47.8, 0.196,   2000.,   5300., 250.,  -1.});
	pft_list.push_back(Pft {"White ash",     130., 1.75 ,     100,   SHADE_TOLERANT,  50.0, 2160., 80.2, 0.802,   2100.,  10700., 320.,  -1.});
	pft_list.push_back(Pft {"Mt. maple",     100., 1.13 ,      25,   SHADE_TOLERANT,  13.5,  500., 53.8, 2.0  ,   2000.,   6300., 320.,  -1.});
	pft_list.push_back(Pft {"Striped maple", 150., 1.75 ,      30,   SHADE_TOLERANT,  22.5, 1000., 76.6, 1.70 ,   2000.,   6300., 320.,  -1.});
	pft_list.push_back(Pft {"Pin cherry",    200., 2.45 ,      30, SHADE_INTOLERANT,  28.5, 1126., 70.6, 1.26 ,   1100.,   8000., 190.,  -1.});
	pft_list.push_back(Pft {"Choke cherry",  150., 2.45 ,      20, SHADE_INTOLERANT,  10.0,  500., 72.6, 3.63 ,    600.,  10000., 155.,  -1.});
	pft_list.push_back(Pft {"Balsam Fir",    200., 2.5  ,      80,   SHADE_TOLERANT,  50.0, 1830., 67.9, 0.679,   1100.,   3700., 190.,  -1.});
	pft_list.push_back(Pft {"Spruce",         50., 2.5  ,     350,   SHADE_TOLERANT,  50.0, 1830., 67.9, 0.679,    600.,   3700., 190.,  -1.});
	pft_list.push_back(Pft {"White birch",   140., 0.486,      80, SHADE_INTOLERANT,  46.0, 1830., 73.6, 0.800,   1100.,   3700., 190., 600.});
	pft_list.push_back(Pft {"Mt. ash",       150., 1.75 ,      30,   SHADE_TOLERANT,  10.0,  500., 72.6, 3.63 ,   2000.,   4000., 300.,  -1.});
	pft_list.push_back(Pft {"Red maple",     240., 1.75 ,     150,   SHADE_TOLERANT, 152.5, 3660., 46.3, 0.152,   2000.,  12400., 300.,  -1.});

	for (int i=0; i<pft_list.size(); i++) {
		Pft& pft = pft_list[i];
		if (pft.type == SHADE_TOLERANT) {
			shade_tolerant_pfts.push_back(i);
		} else {
			shade_intolerant_pfts.push_back(i);
		}
	}
}
