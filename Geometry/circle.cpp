#include"circle.h"
Circle::Circle(Point ct, double r)
{
	cent = ct;
	this->r = r;
}
/*
check_locat(Point &pt)
�ж�ĳ����Բ�е�λ��
Բ�⣺check>0;
Բ��: check==0;
Ժ��: check<0;
*/
double Circle::check_locat(Point& pt)
{
	double check = (pt.x() - cent.x()) * (pt.x() - cent.x())
		+ (pt.y() - cent.y()) * (pt.y() - cent.y()) - r * r;
	return check;
}
