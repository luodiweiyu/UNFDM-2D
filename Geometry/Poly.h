#pragma once
#include"point.h"
#include"line.h"
#include<vector>
using std::vector;
class Poly
{
protected:
	vector <Point> pt;
	vector <Line> ln;
	Point cent;
public:
	Poly() {};
	Poly(const Poly& py);
	void add_pt(Point& point);
	void add_ln(Line& line);
	Point point(int n) { return pt[n]; };
	Line line(int n) { return ln[n]; };
	void order_pt();
	void update_cent();
	int pt_num() { return pt.size(); };
	int ln_num() { return ln.size(); };
};

