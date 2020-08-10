#pragma once
#include"geo_base.h"
#include"../Flowfield/flowfield.h"
#include <vector>
using namespace geo_base;
enum Point_type { none, good, bad };
class Point :public point_base
{
public:
	Point(double x=0, double y=0, double z = 0, int id = 0);
	Point(const Point& pt);
	~Point() { }
	int id() { return ID; };
	void change_id(int id) { ID = id; };
	int neibornum() { return neibor.size(); }
	Point getneibor(int id) { return neibor[id]; }
	int search_neibor(Point& point);//ËÑË÷
	void insertneibor(Point pt);
	void orderNeibor();
	void change_type(Point_type tp);
	void change_coord(double x = 0, double y = 0, double z = 0);
	void position_in_flowfield();
	Point_type gettype();
	Point operator+(const Point& pt);
	Point& operator=(const Point& pt);
	friend double distance(Point& pt1, Point& pt2);
	friend double gettheta(Point& pt1, Point& pt2);
private:
	int ID;
	Point_type point_type;
	std::vector<Point> neibor;
};