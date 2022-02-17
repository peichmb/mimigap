#ifndef GAP_H
#define GAP_H

struct Pft {
	const double h_max;
	const double d_max;
	const double b2;
	const double b3;
	const double g;
	const double c;
};

class Plant {

public:
	void growth();

private:
	Pft& pft;
	double h;
	double d;
};




#endif // GAP_H
