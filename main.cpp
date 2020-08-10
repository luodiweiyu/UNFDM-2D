#include"Flowfield/mesh.h"
#include"Fluid/Solver/SolverFluid.h"
int main()
{
	Mesh mp;
	mp.init();
	mp.output("meshpoint.dat");
	mp.out_poly("poly.dat");
	SolverFluid fluid(mp);
	fluid.solver();
	return 0;
}