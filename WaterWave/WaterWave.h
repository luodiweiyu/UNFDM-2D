#pragma once
#include"../Geometry/point.h"
namespace WaterWave
{
	const double g = 9.8;//�������ٶ�
	const int ThreeNeiborMethod[12][4] = {
{1,2,0,0},//����3
{0,1,2,2},
{2,0,1,1},

{0,1,1,2},//����2
{1,2,2,0},
{2,0,0,1},

{0,0,1,2},//����1
{1,1,2,0},
{2,2,0,1},

{0,1,2,0},//����4
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