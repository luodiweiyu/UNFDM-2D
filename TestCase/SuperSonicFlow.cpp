#include"SuperSonicFlow.h"
#include"../Flowfield/mesh.h"
#include"../Fluid/SuperSonic.h"
#include"../Fluid/Solver/SolverFluid.h"
void testSuperSonicFlow()
{
	using namespace SuperSonic;
	Mesh mp;
	mp.init();
	mp.output("meshpoint.dat");
	mp.out_poly("poly.dat");
	Solver fluid(mp);
	fluid.solver();
}
