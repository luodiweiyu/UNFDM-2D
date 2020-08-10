#pragma once
#include<vector>
using std::vector;
//通量基类
class Flux
{
protected:
	vector<double> var;
public:
	const double dim = 2;
	Flux() {  };
	Flux(Flux& f);
	virtual double& operator[](int i) { return var[i]; };
	double flux(int i)const { return var[i]; }  ;
	virtual Flux operator+(const Flux& f);
	virtual Flux operator-(const Flux& f);
	virtual Flux& operator=(const Flux& f);
	virtual Flux& operator+=(const Flux& f);
	friend Flux operator*(double number, Flux& f);

};