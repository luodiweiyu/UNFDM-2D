#pragma once
#include"../Geometry/point.h"
#include"../Geometry/line.h"
#include"../Geometry/poly.h"
#include<string>
using std::vector;
using std::string;
class Mesh
{
private:
	int min_size = 0;
	vector<Point> pt;
	vector<Line> ln;
	vector<Poly> py;
public:
	Mesh();
	Mesh(const Mesh& mh);
	~Mesh();
	void insert_pt(Point &point);//Ìí¼Óµã
	int search_pt(Point& point);//ËÑË÷
	void insert_ln(Point& pt1, Point& pt2);
	void insert_ln(Line &ln);
	int search_ln(Line& line);
	void insert_py(Poly poly) { py.push_back(poly); };
	void out_poly(string filename);
	void init();
	void output(string filename);
	int ptNum() const { return pt.size(); };
	int lnNum()const  { return ln.size(); };
	int pyNum()const { return py.size(); };
	Point point(int i) { return pt[i]; };
	Line line(int i) { return ln[i]; };
	Poly poly(int i) { return py[i]; };
	friend class SolverFluid;
};
