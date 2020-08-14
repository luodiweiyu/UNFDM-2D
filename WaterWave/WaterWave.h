#pragma once
#include"../Geometry/point.h"
namespace WaterWave
{
	const double g = 9.8;//重力加速度
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
	namespace Boundary {
		const int notBc = 0;
		const int inlet = 1;
		const int outlet = 2;
		const int wall = 3;
		class BoundCondition;
	}
	class Solver;
	namespace Riemann {};
}