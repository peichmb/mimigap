#ifndef GAP_H
#define GAP_H

#include <vector>
#include <list>
#include <string>

class Forest;

// Wrt establishment, there are 3 types of trees in JABOWA v1
typedef enum {CHERRY=0, BIRCH=1, SHADE_TOLERANT=2} tree_type;

// Static parameters of a PFT
struct Pft {
	static int npft;
	const std::string name;
	const int id;
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

	Pft(const char* name, double g, double c, double age_max, tree_type type,
	    double d_max, double h_max, double b2, double b3,
	    double degd_min, double degd_max, double wmin, double wmax);
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
	double basal_area();
	void set_sla(double s);
	double get_sla();
	
	double r_light_test() {
		return r_light();
	}

private:
	int pft_id;
	int tree_age;
	double h; // Height
	double d; // Diameter
	double d_change; // Change in diameter this year
	double w; // Weight
	double ba; // Basal_area
	double sla; // Shading leaf area
	void update_height();
	void update_weight();
	void update_basal_area();
	double r_light();
};

// Plot class
class Plot {

public:
	//Plot(Forest& parent_forest);
	Plot();
	~Plot();

	//Forest& forest;
	// Advance to next time step
	void advance();

	// Return plot info string
	std::string info();

private:

	double weight;
	double basal_area;

	void birth();
	void kill();
	void growth();
	std::list<Tree> trees;
};

// Forest class
class Forest {

public:
	Forest(int nplots);
	int nplots();
	void advance();
	void dump_output();
	~Forest();
private:
	std::vector<Plot> plots;
};

void initialize_gap();

int npft();

void increase_simulation_year();

std::string get_header();

#endif // GAP_H
