#pragma once
#include<vector>
using std::vector;
class MoveMesh
{
private:
	vector<double> meshVel;//网格运动速度
public:
	MoveMesh() {meshVel.resize(3);	};
	void change(double u = 0, double v = 0, double w = 0);
	double u() { return meshVel[0]; };
	double v() { return meshVel[1]; };
	double w() { return meshVel[2]; };
};