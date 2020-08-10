#pragma once
#include<vector>
using std::vector;
//ͨ������
class FluxBase
{
protected:
	vector<double> var;
public:
	const double dim = 2;
	FluxBase() {  };
	FluxBase(FluxBase& f);
	virtual double& operator[](int i) { return var[i]; };
	double flux(int i)const { return var[i]; }  ;
	virtual FluxBase operator+(const FluxBase& f);
	virtual FluxBase operator-(const FluxBase& f);
	virtual FluxBase& operator=(const FluxBase& f);
	virtual FluxBase& operator+=(const FluxBase& f);
	friend FluxBase operator*(double number, FluxBase& f);

};