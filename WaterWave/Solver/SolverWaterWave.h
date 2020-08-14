#pragma once
#include"../WaterWave.h"
#include"../../Flowfield/mesh.h"
#include"../../Time/Time.h"
#include"../WaterWaveVar/WaterWaveVar.h"
#include"../Boundary/Boundary.h"
#include"../Riemann/Riemann.h"
namespace WaterWave
{
	class WaterWave::Solver
	{
	private:
		BaseVar* bv;
		ConsVar* cv;
		Mesh* mh;
		Time time;
		Boundary::BoundCondition* bc;
		int size;
	public:
		Solver(Mesh& mh_) {
			mh = &mh_;
			size = mh_.ptNum();
			bv = new BaseVar[size];
			cv = new ConsVar[size];
			bc = new Boundary::BoundCondition[size];
			updateBC(mh_);
		};
		void init();
		void updateBC(Mesh& mh);
		void solverCore();
		void solver();
		friend FlowFlux solverFourNeibor(Point* localPoint, BaseVar* localBV, Point* neiborPoint, BaseVar* neiborBV);
		friend FlowFlux solverThreeNeibor(Point* localPoint, BaseVar* localBV, Point* neiborPoint, BaseVar* neiborBV);
		void updateBounVar();
		void updateBaseVar();
		void outFlow(string filename);
	};
}
