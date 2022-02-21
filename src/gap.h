#ifndef GAP_H
#define GAP_H

#include <vector>
#include <list>
#include <string>

class Forest;

// Wrt establishment, there are 3 types of trees in JABOWA v. 1
typedef enum {CHERRY=0, BIRCH=1, SHADE_TOLERANT=2} tree_type;

// Static parameters of a PFT
struct Pft {
	const std::string name;
	const double g;
	const double c;
	const double age_max;
	const tree_type type;
	const double d_max;
	const double h_max;
	const double b2;
	const double b3;
	const double degd_min;
	const double degd_max;
	const double wmin;
	const double wmax;
};

// Tree class
class Tree {

public:
	Pft& pft; // Reference to struct with PFT static parameters
	Tree(int pft_id);
	~Tree();
	void growth();
	int age();
	double diameter();
	double diameter_change();
	double height();
	double weight();

private:
	int pft_id;
	int tree_age;
	double h; // Height
	double d; // Diameter
	double d_change; // Change in diameter this year
	double w; // Weight
	void update_height();
	void update_weight();
	double r_light(double al);
};

// Stand class
class Stand {

public:
	//Stand(Forest& parent_forest);
	Stand();
	~Stand();

	//Forest& forest;
	// Advance to next time step
	void advance();

private:

	double weight;

	void birth();
	void kill();
	void growth();
	std::list<Tree> trees;
};

// Forest class
class Forest {

public:
	Forest();
	~Forest();
private:
	double degd;
	std::vector<Stand> stands;
};

void initialize_gap();

#endif // GAP_H
