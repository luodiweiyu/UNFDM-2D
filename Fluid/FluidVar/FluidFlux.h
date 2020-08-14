#pragma once
#include"../../FluxBase/FluxBase.h"
#include"../SuperSonic.h"
namespace SuperSonic
{
	class BaseVar :public FluxBase//基本变量
	{
	public:
		BaseVar() { var.resize(dim+2); };
		BaseVar(double rho,double u,double v,double p);
		//BaseVar(ConsVar& cv);
		void changeBV(double rho, double u, double v, double p);
		void updateFromConsVar(const ConsVar& cv);
		//~BaseVar() { delete[]var; };
		double rho()const  { return var[0]; };
		double u()const { return var[1]; };
		double v() const { return var[2]; };
		double w() const { if (dim == 3) return var[3]; else return 0; };
		double p() const { if (dim == 3) return var[4]; else return var[3]; };
	};

	class ConsVar:public FluxBase//守恒变量
	{
	public:
		ConsVar() { var.resize(dim + 2); };
		ConsVar(double rho, double u, double v, double p);
		ConsVar(BaseVar &bv);
		//~ConsVar() { delete[]var; };
		void updateFromBaseVar(const BaseVar& bv);
		void updateFromBaseVar(double rho, double u, double v, double p);
		ConsVar& operator=(FluxBase& f);
		ConsVar& operator+=(const FluxBase& f);
	};
	
	class FlowFlux :public FluxBase//流动通量
	{
	public:
		FlowFlux() { var.resize(dim + 2); };
		FlowFlux(double f1, double f2, double f3, double f4);
		FlowFlux(const FlowFlux& f);
		void changeFF(double f1, double f2, double f3, double f4);
		FlowFlux& operator=(FluxBase&f);
		FlowFlux& operator=(double number);
		FlowFlux& operator/=(double number);
		FlowFlux operator*(double number);
		FlowFlux& operator+=(const FluxBase& f);
		FlowFlux operator+(const FlowFlux& f);
		FlowFlux operator-(const FlowFlux& f);
		FlowFlux operator/(const double dig);
		//friend FlowFlux operator*(double number, FlowFlux& f);
	};
}
