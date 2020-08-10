#pragma once
#include<vector>
#include"point.h"
#include"circle.h"
using std::vector;
class Circle;
class Line
{
private:
	Point start;
	Point end;
	int ID;
public:
	Line(Point pt1, Point pt2,int id=-1);
	Line() { };
	Line(const Line& ln) { start = ln.start, end = ln.end, ID = ln.ID; };
	Point start_pt() { return start; };
	Point end_pt() { return end; };
	void change_id(int id) { ID = id; };
	int id() { return ID; };
	bool operator ==(const Line& ln)
	{
		return start == ln.start && end == ln.end;
	};
	Line& operator =(const Line& ln)
	{
		start = ln.start;
		end = ln.end;
		return *this; 
	};
	Point linecross(Line& ln);
	Point cross_point_with_flowfield();
	friend Point linecircle_corss(Line ln, Circle cr);
};

