#pragma once
#include<vector>
#include"../FluidVar/FluidFlux.h"
#include"../../Flowfield/mesh.h"
#include"../Boundary/Boundary.h"
#include"../../CoordTrans/coordTrans.h"
#include"../../Time/Time.h"
#include"../../MoveMesh/MoveMesh.h"
using namespace FluidFlux;
using std::vector;
class SolverFluid
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
	SolverFluid(Mesh& mh_) {
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
	//只初始化大小，此处没有初始化边界条件
	//暂时还未想好怎么处理
	//2020年8月3日22:20:23
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
	friend FlowFlux solverFourNeibor(Point* localPoint_bak, Point* localPoint, BaseVar* localBV, Point* neiborPoint, BaseVar* neiborBV);
	friend FlowFlux solverThreeNeibor(Point* localPoint_bak, Point* localPoint, BaseVar* localBV, Point* neiborPoint, BaseVar* neiborBV);
	void moveMesh();
	void updateBounVar();
	void updateBaseVar();
	void outFlow(string filename);
};
