#pragma once
#include<vector>
#include"../Math/math.h"
using std::vector;
/*
几何基础名称空间
由点、线、面基础类构成
*/
namespace geo_base
{
	class point_base
	{
	public:
		point_base(double x = 0, double y = 0, double z = 0);
		double x() const { return coord[0]; };
		double y() const { return coord[1]; };
		double z() const { return coord[2]; };
		void change_x(double x);
		void change_y(double y);
		void change_z(double z);
		virtual bool operator ==(const point_base& pt)
		{
			return abs(coord[0] - pt.coord[0]) < delta &&
				abs(coord[1] - pt.coord[1]) < delta &&
				abs(coord[2] - pt.coord[2]) < delta;
		};
	protected:
		double coord[3];
	};


	class line_base
	{
	protected:
		point_base pt[2];
	public:
		line_base(point_base& pt1, point_base& pt2);
		line_base() {};
		bool operator ==(const line_base& ln)
		{
			return pt[0] == ln.pt[0] &&
				pt[0] == ln.pt[0];
		};

	};
	class poly_base
	{
	protected:
		vector <point_base> pt;
		vector <line_base> ln;
	public:
		poly_base() {};
		void add_pt(point_base& pt);
		void add_ln(line_base& ln);
	};
}

