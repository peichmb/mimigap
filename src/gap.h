#ifndef GAP_H
#define GAP_H

#include <vector>
#include <string>

// Static parameters of a PFT
struct Pft {
	const std::string name;
	const double h_max;
	const double d_max;
	const double b2;
	const double b3;
	const double g;
	const double c;
};

// Tree class
class Tree {

public:
	Tree(int pft_id);
	void growth();
	~Tree();

private:
	int pft_id;
	double h;
	double d;
};

// Stand class
class Stand {

public:
	Stand();
	~Stand();

private:
	std::vector<Tree> trees;
};

#endif // GAP_H
