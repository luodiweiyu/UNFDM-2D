#include"line.h"
#include"circle.h"
#include<iostream>
Line::Line(Point pt1, Point pt2, int id)
{
	Point pt[2];
	if (pt1.x() < pt2.x())
	{
		pt[0] = pt1;
		pt[1] = pt2;
	}
	else if (pt1.x() > pt2.x())
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
	start = pt[0];
	end = pt[1];
	this->ID = id;
}
/*
cross_point(Line &ln)
求解两条线交点
！！现只有2D
https://www.cnblogs.com/DHUtoBUAA/p/8057056.html
ln  线段
*/

Point Line::linecross(Line& ln)
{

	double a1, b1, c1;
	double a2, b2, c2;
	a1 = end.y() - start.y();
	b1 = start.x() - end.x();
	c1 = end.x() * start.y() - start.x() * end.y();

	a2 = ln.end.y() - ln.start.y();
	b2 = ln.start.x() - ln.end.x();
	c2 = ln.end.x() * ln.start.y() - ln.start.x() * ln.end.y();
	double m = a1 * b2 - a2 * b1;

	Point pt;
	if (m != 0)
	{
		pt.change_x((c2 * b1 - c1 * b2) / m);
		pt.change_y((c1 * a2 - c2 * a1) / m);
	}
	else
		throw "无交点";
	return pt;
}
/*
cross_point(Line ln,Circle cr)
使用二分法求解线段与圆的交点
ln  线段
cr  圆
*/
Point  linecircle_corss(Line ln, Circle cr)
{
	if (cr.check_locat(ln.start) * cr.check_locat(ln.end) > 0)
		throw "线段在圆的一侧，出现错误";
	Point p1(ln.start);
	Point p2(ln.end);
	Point pmid;
	while (distance(p1, p2) > delta)
	{
		pmid.change_coord((p1.x() + p2.x()) / 2, (p1.y() + p2.y()) / 2);
		if (cr.check_locat(pmid) == 0)
			break;
		if (cr.check_locat(pmid) * cr.check_locat(p1) > 0)
			p1 = pmid;
		else
			p2 = pmid;
	}
	return pmid;
}

Point Line::cross_point_with_flowfield()
{
	start.position_in_flowfield();
	end.position_in_flowfield();
	if (start.gettype() == good && end.gettype() == good)
		throw "两点均在流场内部！";
	if (start.gettype() == bad && end.gettype() == bad)
		throw "两点均在流场外部！";
	Line left, right, up, down;
	Point ld(xmin, ymin), rd(xmax, ymin), lu(xmin, ymax), ru(xmax, ymax);
	left = Line(ld, lu);
	right = Line(rd, ru);
	up = Line(lu, ru);
	down = Line(ld, rd);
	Circle cr(Point(), r);
	if (start.x() <= xmin || end.x() <= xmin)
		return linecross(left);
	else if (start.x() >= xmax || end.x() >= xmax)
		return linecross(right);
	else if (start.y() <= ymin || end.y() <= ymin)
		return linecross(down);
	else if (start.y() >= ymax || end.y() >= ymax)
		return linecross(up);
	else
		return linecircle_corss(*this, cr);
}

