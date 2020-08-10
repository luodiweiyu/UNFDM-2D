#pragma once
#include"../../Flux/Flux.h"
#include"../FluidPara.h"
namespace FluidFlux
{
	class ConsVar;
	class BaseVar :public Flux//基本变量
	{
	public:
		BaseVar() { var.resize(dim+2); };
		BaseVar(double rho,double u,double v,double p);
		//BaseVar(ConsVar& cv);
		void changeBV(double rho, double u, double v, double p);
		void updateFromConsVar(ConsVar& cv);
		//~BaseVar() { delete[]var; };
		double rho() { return var[0]; };
		double u() { return var[1]; };
		double v() { return var[2]; };
		double w() { if (dim == 3) return var[3]; else return 0; };
		double p() { if (dim == 3) return var[4]; else return var[3]; };
	};

	class ConsVar:public Flux//守恒变量
	{
	public:
		ConsVar() { var.resize(dim + 2); };
		ConsVar(double rho, double u, double v, double p);
		ConsVar(BaseVar &bv);
		//~ConsVar() { delete[]var; };
		void updateFromBaseVar(BaseVar& bv);
		void updateFromBaseVar(double rho, double u, double v, double p);
		ConsVar& operator=(Flux& f);
		ConsVar& operator+=(const Flux& f);
	};
	
	class FlowFlux :public Flux//流动通量
	{
	public:
		FlowFlux() { var.resize(dim + 2); };
		FlowFlux(double f1, double f2, double f3, double f4);
		FlowFlux(const FlowFlux& f);
		void changeFF(double f1, double f2, double f3, double f4);
		FlowFlux& operator=(Flux &f);
		FlowFlux& operator=(double number);
		FlowFlux& operator/=(double number);
		FlowFlux operator*(double number);
		FlowFlux& operator+=(const Flux& f);
		FlowFlux operator+(const FlowFlux& f);
		FlowFlux operator-(const FlowFlux& f);
		//friend FlowFlux operator*(double number, FlowFlux& f);
	};
}
