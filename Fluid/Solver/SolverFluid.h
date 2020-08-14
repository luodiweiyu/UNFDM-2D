#pragma once
#include<vector>
#include"../../Flowfield/mesh.h"
#include"../../CoordTrans/coordTrans.h"
#include"../../Time/Time.h"
#include"../SuperSonic.h"
#include"../../MoveMesh/MoveMesh.h"
#include"../Boundary/Boundary.h"
#include"../FluidVar/FluidFlux.h"
#include"../Riemann/Riemann.h"
using std::vector;
namespace SuperSonic
{
	class Solver
	{
	private:
		BaseVar* bv;
		ConsVar* cv;
		Mesh* mh;
		Mesh mh_bak;
		Time time;
		vector<MoveMesh> move;
		Boundary::BoundCondition* bc;
		int size;
	public:
		Solver(Mesh& mh_) {
			mh = &mh_;
			size = mh_.ptNum();
			bv = new BaseVar[size];
			cv = new ConsVar[size];
			bc = new Boundary::BoundCondition[size];
			move.resize(size);
			updateBC(mh_);
			mh_bak = *mh;
		};
		/*
		//ֻ��ʼ����С���˴�û�г�ʼ���߽�����
		//��ʱ��δ�����ô����
		//2020��8��3��22:20:23
		SolverFluid(int MeshPtNum) {
			size = MeshPtNum,
				bv = new BaseVar[size],
				bc = new Boundary::BoundCondition[size];
		};
		*/
		void initFlow();
		void updateBC(Mesh& mh);
		void solverCore();
		void solver();
		void moveMesh();
		void updateBounVar();
		void updateBaseVar();
		void outFlow(string filename);
		friend FlowFlux solverFourNeibor(double dt, Point* localPoint_bak, Point* localPoint, BaseVar* localBV, Point* neiborPoint, BaseVar* neiborBV);
		friend FlowFlux solverThreeNeibor(double dt, Point* localPoint_bak, Point* localPoint, BaseVar* localBV, Point* neiborPoint, BaseVar* neiborBV);
	};
}
