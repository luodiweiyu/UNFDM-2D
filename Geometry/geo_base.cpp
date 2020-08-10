#include"geo_base.h"
using namespace geo_base;
point_base::point_base(double x, double y, double z)
{
	coord[0] = x;
	coord[1] = y;
	coord[2] = z;
}
void point_base::change_x(double x)
{
	coord[0] = x;
}
void point_base::change_y(double y)
{
	coord[1] = y;
}
void point_base::change_z(double z)
{
	coord[2] = z;
}




line_base::line_base(point_base& pt1, point_base& pt2)
{
	if (pt1.x() < pt2.x())
	{
		pt[0] = pt1;
		pt[1] = pt2;
	}
	else if(pt1.x() > pt2.x())
	{
		pt[0] = pt2;
		pt[1] = pt1;
	}
	else if (pt1.y() < pt2.y())
	{
		pt[0] = pt1;
		pt[1] = pt2;
	}
	else
	{
		pt[0] = pt2;
		pt[1] = pt1;
	}
}



void poly_base::add_pt(point_base &pt)
{
	int i = 0;
	for (i = 0; i < this->pt.size(); i++)
	{
		if (this->pt[i] == pt)
			return;
	}
	this->pt.push_back(pt);
}

void poly_base::add_ln(line_base& ln)
{
	int i = 0;
	for (i = 0; i < this->ln.size(); i++)
	{
		if (this->ln[i] == ln)
			return;
	}
	this->ln.push_back(ln);
}
