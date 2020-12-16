#pragma once
#include"../Geometry/point.h"
#include"../Geometry/line.h"
#include"../Geometry/poly.h"
#include"../Fluid/SuperSonic.h"
#include<string>
using std::vector;
using std::string;
/*
Mesh: 网格类, 流场中的所有网格, 由节点、线元、网格单元（多边形）组成
pt: 网格类中所有的节点
ln: 网格类中所有的线元
py: 网格类中所有的网格单元（多边形）
主要功能：
1.根据相关参数生成网格
2.往现有网格里添加节点、线元、单元
3.查询一节点、线元是否已在网格类中存在
4.输出所有节点、整个网格
5.访问对应序号的节点、线元、单元
*/
class Mesh
{
private:
	int min_size = 0;
	vector<Point> pt;
	vector<Line> ln;
	vector<Poly> py;
public:
	Mesh();
	Mesh(const Mesh& mh);
	~Mesh();
	void insert_pt(Point &point);//添加点
	int search_pt(Point& point);//搜索点
	void insert_ln(Point& pt1, Point& pt2);//插入线元（以两个点的方式）
	void insert_ln(Line &ln);//插入线元（以线的方式）
	int search_ln(Line& line);//搜索线元
	void insert_py(Poly poly) { py.push_back(poly); };//插入单元
	void out_poly(string filename);//输出整个网格
	void init();//网格初始化，根据参数生成计算网格|后期可以更改内部规则，从文件读入或其他等
	void output(string filename);//输出所有节点 pt
	int ptNum() const { return pt.size(); };//输出节点的数目
	int lnNum()const  { return ln.size(); };//输出线元的数目
	int pyNum()const { return py.size(); };//输出单元的数目
	Point point(int i) { return pt[i]; };//访问第i个节点
	Line line(int i) { return ln[i]; };//访问第i个线元
	Poly poly(int i) { return py[i]; };//访问第i个单元
	friend class SuperSonic::Solver;
};
