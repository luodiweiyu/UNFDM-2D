#pragma once
//#include"../Fluid/Solver/SolverFluid.h"
#include"../Fluid/FluidVar/FluidFlux.h"
#include"../Flowfield/mesh.h"
using FluidFlux::BaseVar;
//class SolverFluid;
class Time
{
private:
	double tStart;
	double tCurrent;
	double tEnd;
	double dt;
	double CFL;
public:
	Time(double tStart_=0, double tEnd_=100, double CFL_=0.9);
	void init(double tStart_ = 0, double tEnd_ = 100, double CFL_ = 0.5);
	void update(BaseVar& bv, Mesh& mh);
	double startTime() { return tStart; };
	double currentTime() { return tCurrent; };
	double endTime() { return tEnd; };
	double deltaT() { return dt; };
	double cfl() { return CFL; };
	void updateTCurrent() { tCurrent += dt; };
};

