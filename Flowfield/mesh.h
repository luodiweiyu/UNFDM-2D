#pragma once
#include"../Geometry/point.h"
#include"../Geometry/line.h"
#include"../Geometry/poly.h"
#include"../Fluid/SuperSonic.h"
#include<string>
using std::vector;
using std::string;
/*
Mesh: ������, �����е���������, �ɽڵ㡢��Ԫ������Ԫ������Σ����
pt: �����������еĽڵ�
ln: �����������е���Ԫ
py: �����������е�����Ԫ������Σ�
��Ҫ���ܣ�
1.������ز�����������
2.��������������ӽڵ㡢��Ԫ����Ԫ
3.��ѯһ�ڵ㡢��Ԫ�Ƿ������������д���
4.������нڵ㡢��������
5.���ʶ�Ӧ��ŵĽڵ㡢��Ԫ����Ԫ
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
	void insert_pt(Point &point);//��ӵ�
	int search_pt(Point& point);//������
	void insert_ln(Point& pt1, Point& pt2);//������Ԫ����������ķ�ʽ��
	void insert_ln(Line &ln);//������Ԫ�����ߵķ�ʽ��
	int search_ln(Line& line);//������Ԫ
	void insert_py(Poly poly) { py.push_back(poly); };//���뵥Ԫ
	void out_poly(string filename);//�����������
	void init();//�����ʼ�������ݲ������ɼ�������|���ڿ��Ը����ڲ����򣬴��ļ������������
	void output(string filename);//������нڵ� pt
	int ptNum() const { return pt.size(); };//����ڵ����Ŀ
	int lnNum()const  { return ln.size(); };//�����Ԫ����Ŀ
	int pyNum()const { return py.size(); };//�����Ԫ����Ŀ
	Point point(int i) { return pt[i]; };//���ʵ�i���ڵ�
	Line line(int i) { return ln[i]; };//���ʵ�i����Ԫ
	Poly poly(int i) { return py[i]; };//���ʵ�i����Ԫ
	friend class SuperSonic::Solver;
};
