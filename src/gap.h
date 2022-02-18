#ifndef GAP_H
#define GAP_H

#include <vector>
#include <list>
#include <string>

class Forest;

// There are 2 types of tree in JABOWA 1:
typedef enum {SHADE_INTOLERANT=1, SHADE_TOLERANT=2} tree_type;

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
	double diameter();
	double height();

private:
	int pft_id;
	double h;
	double d;
	double r_light(double al);
	void update_height();
};

// Stand class
class Stand {

public:
	//Forest& forest;
	double weight;
	double weight_cherry;
	double weight_birch;
	//Stand(Forest& parent_forest);
	Stand();
	~Stand();

private:
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
