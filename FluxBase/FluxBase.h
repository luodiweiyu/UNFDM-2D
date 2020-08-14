#pragma once
#include<vector>
using std::vector;
//通量基类
class FluxBase
{
protected:
	vector<double> var;
public:
	const double dim = 2;
	FluxBase() { };
	FluxBase(FluxBase& f);
	virtual double operator[]  (int i)const { return var[i]; }
	double flux(int i)const { return var[i]; };
	FluxBase operator+(const FluxBase& f);
	FluxBase operator-(const FluxBase& f);
	FluxBase& operator=(const FluxBase& f);
	FluxBase& operator+=(const FluxBase& f);
	friend FluxBase operator*(double number, FluxBase& f);

};