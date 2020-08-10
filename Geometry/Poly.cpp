#include "Poly.h"
Poly::Poly(const Poly& py)
{
	pt = py.pt;
	ln = py.ln;
	cent = py.cent;
}
void Poly::add_pt(Point& point)
{
	int i;
	for (i = 0; i < pt.size(); i++)
	{
		if (pt[i] == point)
			return;
	}
	pt.push_back(point);
	update_cent();
}
void Poly::order_pt()
{
	int i, j;
	if (pt.size() < 3)
		throw "������������������ܹ�������";
	double* theta = new double[pt.size()];
	double theta_temp;
	Point pt_temp;
	//���ÿ���ڵ������ĵ����߶�x�ļн�
	for (i = 0; i < pt.size(); i++)
		theta[i] = gettheta(cent, pt[i]);
	/// <summary>
	/// ð�ݷ���theta����
	/// ��pt����
	/// </summary>
	for (i = 0; i < pt.size() - 1; i++)
	{
		for (j = 0; j < pt.size() - 1; j++)
		{
			if (theta[j] > theta[j + 1])
			{
				theta_temp = theta[j];
				theta[j] = theta[j + 1];
				theta[j + 1] = theta_temp;
				pt_temp = pt[j];
				pt[j] = pt[j + 1];
				pt[j + 1] = pt_temp;
			}
		}

	}
}

void Poly::add_ln(Line& ln)
{
	int i = 0;
	for (i = 0; i < this->ln.size(); i++)
	{
		if (this->ln[i] == ln)
			return;
	}
	this->ln.push_back(ln);
}
void Poly::update_cent()
{
	cent.change_coord(0, 0, 0);
	for (int i = 0; i < pt.size(); i++)
		cent.change_coord(cent.x() + pt[i].x(), cent.y() + pt[i].y(), cent.z() + pt[i].z());
	cent.change_coord(cent.x() / pt.size(), cent.y() / pt.size(), cent.z() / pt.size());
}
