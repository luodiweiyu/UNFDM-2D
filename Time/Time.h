#pragma once
//#include"../Fluid/Solver/SolverFluid.h"
#include"../Fluid/SuperSonic.h"
#include"../Fluid/FluidVar/FluidFlux.h"
#include"../Flowfield/mesh.h"
//#include"../WaterWave/WaterWaveVar/WaterWaveVar.h"
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
	void update(SuperSonic::BaseVar& bv, Mesh& mh);
	void update(double dt_) { dt = dt_; };
	//void update(WaterWave::BaseVar& bv, Mesh& mh);
	double startTime() { return tStart; };
	double currentTime() { return tCurrent; };
	double endTime() { return tEnd; };
	double deltaT() { return dt; };
	double cfl() { return CFL; };
	void updateTCurrent() { tCurrent += dt; };
};

