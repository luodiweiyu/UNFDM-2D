#include"point.h"
#include"../Math/math.h"
Point::Point(double x, double y, double z, int id)
{
	this->ID = id;
	coord[0] = x;
	coord[1] = y;
	coord[2] = z;
	point_type = none;
}
Point::Point(const Point& pt)
{
	coord[0] = pt.coord[0];
	coord[1] = pt.coord[1];
	coord[2] = pt.coord[2];
	ID = pt.ID;
	point_type = pt.point_type;
	neibor = pt.neibor;
}
void Point::insertneibor(Point pt)
{
	int i = 0;
	Point ptTemp;
	ptTemp.change_coord(pt.x(), pt.y(), pt.z());
	ptTemp.change_type(pt.gettype());
	ptTemp.change_id(pt.id());
	//为何复制？2020.07.31
	//如果直接存pt，由pt.neibor导致的程序的运行十分缓慢！
	//在后续的计算中应该有办法处理，暂时技术能力不支持。。。
	if (search_neibor(ptTemp) < 0)
		neibor.push_back(ptTemp);
	orderNeibor();
}
int Point::search_neibor(Point& point)//搜索
{
	static int i;
	for (i = 0; i < neibor.size(); i++)
	{
		if (neibor[i] == point)
			return i;
	}
	return -1;
}
void Point::orderNeibor()
{
	double* theta = new double[neibor.size()];
	double theta_temp;
	Point pt_temp;
	int i, j;
	for (i = 0; i < neibor.size(); i++)
		theta[i] = gettheta(*this, neibor[i]);
	for (i = 0; i < int(neibor.size() - 1); i++)
	{
		for (j = 0; j < int(neibor.size() - 1); j++)
		{
			if (theta[j] > theta[j + 1])
			{
				theta_temp = theta[j];
				theta[j] = theta[j + 1];
				theta[j + 1] = theta_temp;
				pt_temp = neibor[j];
				neibor[j] = neibor[j + 1];
				neibor[j + 1] = pt_temp;
			}
		}
	}
}

void Point::change_coord(double x, double y, double z)
{
	change_x(x);
	change_y(y);
	change_z(z);
}

void Point::change_type(Point_type tp)
{
	point_type = tp;
}
Point_type Point::gettype()
{
	return point_type;
}
Point Point::operator+(const Point& pt)
{
	Point pt_out;
	pt_out.change_coord(coord[0] + pt.coord[0], coord[1] + pt.coord[1]);
	return pt_out;
}
Point& Point::operator=(const Point &pt)
{
	change_coord(pt.coord[0], pt.coord[1]);
	ID = pt.ID;
	return *this;
}
double distance(Point& pt1, Point& pt2)
{
	double dis;
	dis = (pt1.coord[0] - pt2.coord[0]) * (pt1.coord[0] - pt2.coord[0])
		+ (pt1.coord[1] - pt2.coord[1]) * (pt1.coord[1] - pt2.coord[1]);
	return sqrt(dis);
}
/*
gettheta(Point& pt1, Point& pt2)
求出向量pt1->pt2与x轴的夹角（0-2pi)
注意顺序
*/
double gettheta(Point& pt1, Point& pt2)
{
	double x = pt2.x() - pt1.x();
	double y = pt2.y() - pt1.y();
	double theta = atan2(y, x);
	if (theta < 0)
		theta += 2 * pi;
	return theta;
}

void Point::position_in_flowfield()
{
	if (coord[0] < xmin || coord[0] > xmax)
		point_type = bad;
	else if (coord[1] < ymin || coord[1] > ymax)
		point_type = bad;
	//else if (coord[0] * coord[0] + coord[1] * coord[1] < r * r)
	//	point_type = bad;
	else
		point_type = good;
}