#pragma once
#include"point.h"
#include"line.h"
class Line;
class Circle
{
private:
	Point cent;
	double r;
public:
	Circle() {};
	Circle(Point ct, double r);
	double check_locat(Point& pt);
	friend Point linecircle_corss(Line ln, Circle cr);
};
