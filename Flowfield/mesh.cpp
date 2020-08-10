#include"mesh.h"
#include"flowfield.h"
#include<fstream>
#include<iostream>
Mesh::Mesh()
{
	pt.resize(min_size);
}
Mesh::Mesh(const Mesh &mh)
{
	pt = mh.pt;
	ln = mh.ln;
	py = mh.py;
}
Mesh::~Mesh()
{
	pt.clear();
}

void Mesh::init()
{
	Point cent(xmin - dl, ymin - dl);
	int n = -1;
	Point polypt[6];
	while (cent.y() <= ymax + dl)
	{
		while (cent.x() <= xmax + dl)
		{
			Point pt_temp;
			Line ln_temp;
			Poly py_temp;
			polypt[0].change_coord(cent.x() + dl, cent.y());
			polypt[1].change_coord(cent.x() + dl / 2, cent.y() + dl * sqrt(3) / 2);
			polypt[2].change_coord(cent.x() - dl / 2, cent.y() + dl * sqrt(3) / 2);
			polypt[3].change_coord(cent.x() - dl, cent.y());
			polypt[4].change_coord(cent.x() - dl / 2, cent.y() - dl * sqrt(3) / 2);
			polypt[5].change_coord(cent.x() + dl / 2, cent.y() - dl * sqrt(3) / 2);
			for (int i = 0; i < 6; i++)
				polypt[i].position_in_flowfield();
			for (int i = 0; i < 6; i++)
			{
				if (polypt[i].gettype() == good)
				{
					insert_pt(polypt[i]);
					py_temp.add_pt(pt[search_pt(polypt[i])]);
				}
				else if (i == 0)
				{
					if (polypt[i + 1].gettype() == good)
					{
						ln_temp = Line(polypt[0], polypt[i + 1]);
						pt_temp = ln_temp.cross_point_with_flowfield();
						insert_pt(pt_temp);
						py_temp.add_pt(pt[search_pt(pt_temp)]);
					}
					if (polypt[5].gettype() == good)
					{
						ln_temp = Line(polypt[0], polypt[5]);
						pt_temp = ln_temp.cross_point_with_flowfield();
						insert_pt(pt_temp);
						py_temp.add_pt(pt[search_pt(pt_temp)]);
					}
				}
				else if (i == 5)
				{
					if (polypt[0].gettype() == good)
					{
						ln_temp = Line(polypt[5], polypt[0]);
						pt_temp = ln_temp.cross_point_with_flowfield();
						insert_pt(pt_temp);
						py_temp.add_pt(pt[search_pt(pt_temp)]);
					}
					if (polypt[i - 1].gettype() == good)
					{
						ln_temp = Line(polypt[5], polypt[i - 1]);
						pt_temp = ln_temp.cross_point_with_flowfield();
						insert_pt(pt_temp);
						py_temp.add_pt(pt[search_pt(pt_temp)]);
					}
				}
				else
				{
					if (polypt[i - 1].gettype() == good)
					{
						ln_temp = Line(polypt[i], polypt[i - 1]);
						pt_temp = ln_temp.cross_point_with_flowfield();
						insert_pt(pt_temp);
						py_temp.add_pt(pt[search_pt(pt_temp)]);
					}
					if (polypt[i + 1].gettype() == good)
					{
						ln_temp = Line(polypt[i], polypt[i + 1]);
						pt_temp = ln_temp.cross_point_with_flowfield();
						insert_pt(pt_temp);
						py_temp.add_pt(pt[search_pt(pt_temp)]);
					}
				}
				pt_temp = Point(xmin, ymin);
				if (distance(cent, pt_temp) < dl)
				{
					insert_pt(pt_temp);
					py_temp.add_pt(pt[search_pt(pt_temp)]);
				}
				pt_temp = Point(xmin, ymax);
				if (distance(cent, pt_temp) < dl)
				{
					insert_pt(pt_temp);
					py_temp.add_pt(pt[search_pt(pt_temp)]);
				}
				pt_temp = Point(xmax, ymin);
				if (distance(cent, pt_temp) < dl)
				{
					insert_pt(pt_temp);
					py_temp.add_pt(pt[search_pt(pt_temp)]);
				}
				pt_temp = Point(xmax, ymax);
				if (distance(cent, pt_temp) < dl)
				{
					insert_pt(pt_temp);
					py_temp.add_pt(pt[search_pt(pt_temp)]);
				}
			}
			if (py_temp.pt_num() >= 3)
			{
				py_temp.order_pt();
				for (int j = 0; j < py_temp.pt_num(); j++)
				{
					if (j != py_temp.pt_num() - 1)
						ln_temp = Line(py_temp.point(j), py_temp.point(j + 1));
					else
						ln_temp = Line(py_temp.point(j), py_temp.point(0));
					insert_ln(ln_temp);
					py_temp.add_ln(ln[search_ln(ln_temp)]);
				}
				insert_py(py_temp);
			}
			cent.change_coord(cent.x() + 3 * dl, cent.y());
		}
		n = -n;
		cent.change_coord(xmin + (1 + n) * 0.75 * dl, cent.y() + dl * sqrt(3) / 2);
	}
}

void Mesh::insert_pt(Point &point)
{
	if (search_pt(point) < 0)
	{
		Point p(point.x(), point.y(), 0, pt.size());
		p.position_in_flowfield();
		pt.push_back(p);
	}
}

/*
查找节点
如果存在返回编号；
不存在返回-1
*/
int Mesh::search_pt(Point& point)
{
	int i = 0;
	for (i = 0; i < int(pt.size()); i++)
	{
		if (abs(pt[i].x() - point.x()) < delta && abs(pt[i].y() - point.y()) < delta)
			return i;
	}
	return -1;
}
/*
对网格所含的节点进行排序；
按照绕中心点逆时针排序
*/
void Mesh::insert_ln(Point& pt1, Point& pt2)
{
	Line ln_temp(pt1, pt2);
	insert_ln(ln_temp);
}
void Mesh::insert_ln(Line &ln)
{
	if (search_ln(ln) < 0)
	{
		ln.change_id(this->ln.size());
		int startId = ln.start_pt().id();
		int endId = ln.end_pt().id();
		pt[endId].insertneibor(pt[startId]);
		pt[startId].insertneibor(pt[endId]);
		this->ln.push_back(ln);
	}
}
int Mesh::search_ln(Line& line)
{
	for (int i = 0; i < ln.size(); i++)
		if (ln[i].start_pt() == line.start_pt() && ln[i].end_pt() == line.end_pt())
			return i;
	return -1;
}

void Mesh::output(std::string filename)
{
	std::ofstream fout(filename);
	fout << "variables = x,y" << std::endl;
	for (int i = 0; i < pt.size(); i++)
	{
		if (pt[i].gettype() == good)
			fout << pt[i].x() << " " << pt[i].y() << std::endl;
	}
}
void Mesh::out_poly(string filename)
{
	using std::ofstream;
	using std::endl;
	int i;
	int face_num = 0;
	for (i = 0; i < py.size(); i++)
		face_num += py[i].ln_num();

	ofstream fout(filename);
	fout << "variables = x,y,p" << endl;
	fout << "zone T=\"test\"" << endl;
	fout << "zonetype = fepolygon" << endl;
	fout << "nodes = " << pt.size() << endl;
	fout << "elements = " << py.size() << endl;
	fout << "faces = " << face_num << endl;
	fout << "NumConnectedBoundaryFaces = 0" << endl;
	fout << "TotalNumBoundaryConnections = 0" << endl;

	for (i = 0; i < pt.size(); i++)
	{
		fout << pt[i].x() << "  ";
		if (i % 20 == 0)
			fout << endl;
	}
	fout << endl;

	fout << endl;
	for (i = 0; i < pt.size(); i++)
	{
		fout << pt[i].y() << "  ";
		if (i % 20 == 0)
			fout << endl;
	}
	fout << endl;
	for (i = 0; i < pt.size(); i++)
	{
		fout << pt[i].neibornum() << "  ";
		if (i % 20 == 0)
			fout << endl;
	}
	fout << endl;

	for (i = 0; i < py.size(); i++)
	{
		for (int j = 0; j < py[i].pt_num() - 1; j++)
		{
			fout << py[i].point(j).id() + 1 << "  " << py[i].point(j + 1).id() + 1 << endl;
		}
		fout << py[i].point(py[i].pt_num() - 1).id() + 1 << "  " << py[i].point(0).id() + 1 << endl;
	}

	//for (i = 0; i < py.size(); i++)
	//{
	//	for (int j = 0; j < py[i].ln_num(); j++)
	//		fout << py[i].line(j).id() + 1 << "  ";
	//	fout << endl;
	//}
	//fout << endl;
	int num = 1;
	for (i = 0; i < py.size(); i++)
	{
		for (int j = 0; j < py[i].ln_num(); j++)
			fout << num << "  ";
		num++;
		fout << endl;
	}
	for (i = 0; i < py.size(); i++)
	{
		for (int j = 0; j < py[i].ln_num(); j++)
			fout << 0 << "  ";
		fout << endl;
	}

}
