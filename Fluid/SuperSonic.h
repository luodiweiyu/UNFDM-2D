#pragma once
#include"../Geometry/point.h"
#include"../CoordTrans/coordTrans.h"
namespace SuperSonic
{
	const double gama = 1.4;
	const int ThreeNeiborMethod[12][4] = {
	{1,2,0,0},//方法3
	{0,1,2,2},
	{2,0,1,1},

	{0,1,1,2},//方法2
	{1,2,2,0},
	{2,0,0,1},

	{0,0,1,2},//方法1
	{1,1,2,0},
	{2,2,0,1},

	{0,1,2,0},//方法4
	{2,0,1,2},
	{1,2,0,1},
	};

	class BaseVar;
	class ConsVar;
	class FlowFlux;
	namespace Boundary {};
	class Solver;
	namespace Riemann
	{
		FlowFlux HLLC_Χ(BaseVar& CL, BaseVar& CR, coordTrans& ct);//半点左侧右侧格点，坐标变换参考点
		FlowFlux HLLC_Y(BaseVar& CD, BaseVar& CU, coordTrans& ct);//半点左侧右侧格点，坐标变换参考点
	};
	//FlowFlux solverFourNeibor(double dt, Point* localPoint_bak, Point* localPoint, BaseVar* localBV, Point* neiborPoint, BaseVar* neiborBV);
	//FlowFlux solverThreeNeibor(double dt, Point* localPoint_bak, Point* localPoint, BaseVar* localBV, Point* neiborPoint, BaseVar* neiborBV);
}
