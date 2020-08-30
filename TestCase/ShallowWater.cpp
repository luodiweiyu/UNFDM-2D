#include"ShallowWater.h"
#include"../Flowfield/mesh.h"
#include"../WaterWave/Solver/SolverWaterWave.h"
void testShallowWater()
{
	using namespace WaterWave;
	Mesh mp;
	mp.init();
	//mp.output("meshpoint.dat");
	//mp.out_poly("poly.dat");
	Solver ShallowWater(mp);
	ShallowWater.solver();
}
