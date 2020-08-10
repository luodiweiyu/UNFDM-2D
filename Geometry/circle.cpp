#include"circle.h"
Circle::Circle(Point ct, double r)
{
	cent = ct;
	this->r = r;
}
/*
check_locat(Point &pt)
判断某点在圆中的位置
圆外：check>0;
圆上: check==0;
院内: check<0;
*/
double Circle::check_locat(Point& pt)
{
	double check = (pt.x() - cent.x()) * (pt.x() - cent.x())
		+ (pt.y() - cent.y()) * (pt.y() - cent.y()) - r * r;
	return check;
}
