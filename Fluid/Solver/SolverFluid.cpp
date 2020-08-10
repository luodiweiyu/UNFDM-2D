#include"SolverFluid.h"
#include"../FluidPara.h"
#include"../Riemann/Riemann.h"
#include<iostream>
#include<fstream>
using namespace Riemann;
void SolverFluid::initFlow()
{
	int i;
	for (i = 0; i < size; i++)
	{
		bv[i].changeBV(19.28571, 1.82312, 0, 41.3333);
		cv[i].updateFromBaseVar(bv[i]);
	}
}
void SolverFluid::updateBC(Mesh& mh)
{
	int i;
	for (i = 0; i < mh.ptNum(); i++)
		bc[i].updateBC(mh.point(i));
}

void SolverFluid::updateBounVar()
{
	int i, j;
	int neiborNum;
	int id;
	int num;
	BaseVar bvTemp;
	using namespace Boundary;
	for (i = 0; i < size; i++)
	{
		if (bc[i].bcType() == notBc)
			continue;
		else if (bc[i].bcType() == inlet)
			bv[i].changeBV(19.28571, 1.82312, 0, 41.3333);

		//bv[i].changeBV(5, 4.1749, 0, 4);
		else
		{
			neiborNum = mh->point(i).neibornum();
			bvTemp.changeBV(0, 0, 0, 0);
			num = 0;
			if (neiborNum == 2)
			{
				for (j = 0; j < neiborNum; j++)
				{
					id = mh->point(i).getneibor(j).id();
					bvTemp.changeBV(bvTemp.rho() + bv[id].rho(),
						bvTemp.u() + bv[id].u(),
						bvTemp.v() + bv[id].v(),
						bvTemp.p() + bv[id].p());
					num++;
				}
			}
			else
			{
				for (j = 0; j < neiborNum; j++)
				{
					id = mh->point(i).getneibor(j).id();
					if (bc[id].bcType() == notBc)
					{
						bvTemp.changeBV(bvTemp.rho() + bv[id].rho(),
							bvTemp.u() + bv[id].u(),
							bvTemp.v() + bv[id].v(),
							bvTemp.p() + bv[id].p());
						num++;
					}
				}

			}
			bv[i].changeBV(bvTemp.rho() / num, bvTemp.u() / num, bvTemp.v() / num, bvTemp.p() / num);
		}
	}
}
void SolverFluid::updateBaseVar()
{
	int i;
	for (i = 0; i < size; i++)
		bv[i].updateFromConsVar(cv[i]);
}

FlowFlux solverFourNeibor(double dt, Point* localPoint_bak, Point* localPoint, BaseVar* localBV, Point* neiborPoint, BaseVar* neiborBV)
{

	coordTrans localCT(dt, *localPoint, *localPoint_bak, neiborPoint[0], neiborPoint[2], neiborPoint[1], neiborPoint[3]);
	FlowFlux F1 = HLLC_Χ(neiborBV[2], *localBV, localCT);
	FlowFlux F2 = HLLC_Χ(*localBV, neiborBV[0], localCT);
	FlowFlux G1 = HLLC_Y(neiborBV[3], *localBV, localCT);
	FlowFlux G2 = HLLC_Y(*localBV, neiborBV[1], localCT);
	FlowFlux localFF = F2 - F1 + G2 - G1;
	return localFF;
}
FlowFlux solverThreeNeibor(double dt, Point* localPoint_bak, Point* localPoint, BaseVar* localBV, Point* neiborPoint, BaseVar* neiborBV)
{
	int i, n0, n1, n2, n3;
	Point neiborPoint_4[4];
	BaseVar neiborBV_4[4];
	FlowFlux localFF;
	localFF = 0;
	for (i = 0; i < 12; i++)
	{
		n0 = ThreeNeiborMethod[i][0];
		n1 = ThreeNeiborMethod[i][1];
		n2 = ThreeNeiborMethod[i][2];
		n3 = ThreeNeiborMethod[i][3];
		neiborBV_4[0] = neiborBV[n0];
		neiborBV_4[1] = neiborBV[n1];
		neiborBV_4[2] = neiborBV[n2];
		neiborBV_4[3] = neiborBV[n3];
		neiborPoint_4[0] = neiborPoint[n0];
		neiborPoint_4[1] = neiborPoint[n1];
		neiborPoint_4[2] = neiborPoint[n2];
		neiborPoint_4[3] = neiborPoint[n3];
		//std::cout << localFF.flux(0) << " " << localFF.flux(1) << " " << localFF.flux(2) << " " << localFF.flux(3) << std::endl;
		localFF += solverFourNeibor(dt, localPoint_bak, localPoint, localBV, neiborPoint_4, neiborBV_4);
		//std::cout << localFF.flux(0) << " " << localFF.flux(1) << " " << localFF.flux(2) << " " << localFF.flux(3) << std::endl;
	}
	localFF /= 12;
	//std::cout << localFF.flux(0) << " " << localFF.flux(1) << " " << localFF.flux(2) << " " << localFF.flux(3) << std::endl;
	return localFF;
}
void SolverFluid::solverCore()
{
	int i, j, neiborid;
	Point neiborPoint[4];
	BaseVar neiborBV[4];
	FlowFlux localFF;
	for (i = 0; i < mh->ptNum(); i++)
	{
		cv[i].updateFromBaseVar(bv[i]);
		if (bc[i].bcType() != Boundary::notBc)
			continue;
		if (mh->point(i).neibornum() == 3)
		{
			for (j = 0; j < mh->point(i).neibornum(); j++)
			{
				neiborid = mh->point(i).getneibor(j).id();
				neiborPoint[j] = mh->point(neiborid);
				neiborBV[j] = bv[neiborid];
			}
			localFF = solverThreeNeibor(time.deltaT(), &mh_bak.point(i), &mh->point(i), &bv[i], neiborPoint, neiborBV);
		}
		else
		{
			for (j = 0; j < mh->point(i).neibornum(); j++)
			{
				neiborid = mh->point(i).getneibor(j).id();
				neiborPoint[j] = mh->point(neiborid);
				neiborBV[j] = bv[neiborid];
			}
			localFF = solverFourNeibor(time.deltaT(), &mh_bak.point(i), &mh->point(i), &bv[i], neiborPoint, neiborBV);
		}
		cv[i] += localFF * (-time.deltaT());
	}
}
void SolverFluid::solver()
{
	time.init();
	initFlow();
	outFlow("mesh.dat");
	int count = 0;
	while (time.currentTime() < time.endTime())
	{
		mh_bak = *mh;//备份上一时刻的网格值;
		moveMesh();
		time.update(*bv, *mh);
		solverCore();
		updateBaseVar();
		updateBounVar();
		if (count % 10 == 0)
		{
			outFlow("data/t=" + std::to_string(time.currentTime()) + ".dat");
			std::cout << "step = " << count << "  time = " << time.currentTime() << std::endl;
		}
		count++;
		time.updateTCurrent();
	}
}

void SolverFluid::outFlow(string filename)
{
	using std::ofstream;
	using std::endl;
	int i;
	int face_num = 0;
	for (i = 0; i < mh->pyNum(); i++)
		face_num += mh->poly(i).ln_num();

	ofstream fout(filename);
	fout << "variables = x,y,rho,u,v,p" << endl;
	fout << "zone T=\"test\"" << endl;
	fout << "zonetype = fepolygon" << endl;
	fout << "nodes = " << mh->ptNum() << endl;
	fout << "elements = " << mh->pyNum() << endl;
	fout << "faces = " << face_num << endl;
	fout << "NumConnectedBoundaryFaces = 0" << endl;
	fout << "TotalNumBoundaryConnections = 0" << endl;
	fout << "solutiontime = " << time.currentTime() << endl;

	for (i = 0; i < mh->ptNum(); i++)
	{
		fout << mh->point(i).x() << "  ";
		if (i % 20 == 0)
			fout << endl;
	}
	fout << endl;

	fout << endl;
	for (i = 0; i < mh->ptNum(); i++)
	{
		fout << mh->point(i).y() << "  ";
		if (i % 20 == 0)
			fout << endl;
	}
	fout << endl;
	for (i = 0; i < mh->ptNum(); i++)
	{
		fout << bv[i].rho() << "  ";
		if (i % 20 == 0)
			fout << endl;
	}
	fout << endl;
	for (i = 0; i < mh->ptNum(); i++)
	{
		fout << bv[i].u() << "  ";
		if (i % 20 == 0)
			fout << endl;
	}
	fout << endl;
	for (i = 0; i < mh->ptNum(); i++)
	{
		fout << bv[i].v() << "  ";
		if (i % 20 == 0)
			fout << endl;
	}
	fout << endl;
	for (i = 0; i < mh->ptNum(); i++)
	{
		fout << bv[i].p() << "  ";
		if (i % 20 == 0)
			fout << endl;
	}
	fout << endl;

	for (i = 0; i < mh->pyNum(); i++)
	{
		for (int j = 0; j < mh->poly(i).pt_num() - 1; j++)
		{
			fout << mh->poly(i).point(j).id() + 1 << "  " << mh->poly(i).point(j + 1).id() + 1 << endl;
		}
		fout << mh->poly(i).point(mh->poly(i).pt_num() - 1).id() + 1 << "  " << mh->poly(i).point(0).id() + 1 << endl;
	}

	//for (i = 0; i < py.size(); i++)
	//{
	//	for (int j = 0; j < py[i].ln_num(); j++)
	//		fout << py[i].line(j).id() + 1 << "  ";
	//	fout << endl;
	//}
	//fout << endl;
	int num = 1;
	for (i = 0; i < mh->pyNum(); i++)
	{
		for (int j = 0; j < mh->poly(i).ln_num(); j++)
			fout << num << "  ";
		num++;
		fout << endl;
	}
	for (i = 0; i < mh->pyNum(); i++)
	{
		for (int j = 0; j < mh->poly(i).ln_num(); j++)
			fout << 0 << "  ";
		fout << endl;
	}
	fout.close();
}
void SolverFluid::moveMesh()
{
	int i;
	static double refX1;
	static double refY1;
	static double refX2;
	static double refY2;
	double refX;
	double l;
	if (time.currentTime() == 0)
	{
		refX1 = (xmax - xmin) / 2;
		refY1 = ymin;
		refX2 = (xmax - xmin) / 2;
		refY2 = ymax;
	}
	for (i = 0; i < size; i++)
	{
		if (mh->point(i).x()>xmin&& mh->point(i).x() < xmax&& mh->point(i).y() > ymin)
		{
			refX = refX1 + (refX2 - refX1) * (mh_bak.pt[i].y() - refY1) / (refY2 - refY1);
			double sideLeftPt = (refY2 - refY1) * xmin - (refX2 - refX1) * ymin + refX2 * refY1 - refX1 * refY2;
			double sidelocalPt = (refY2 - refY1) * mh_bak.pt[i].x() - (refX2 - refX1) * mh_bak.pt[i].y() + refX2 * refY1 - refX1 * refY2;
			if (sideLeftPt * sidelocalPt > 0)
			{
				l = (mh_bak.pt[i].x() - xmin) / (refX - xmin);
				refX = refX1 + (refX1 + 0.2 * sin(time.currentTime() * 20) - refX1) * (mh_bak.pt[i].y() - refY1) / ( refY2 - refY1);
				mh->pt[i].change_x(xmin + l * (refX - xmin));

			}
			else
			{
				l = (xmax - mh_bak.pt[i].x()) / (xmax - refX);
				refX = refX1 + (refX1 + 0.2 * sin(time.currentTime() * 20) - refX1) * (mh_bak.pt[i].y() - refY1) / ( refY2 - refY1);
				mh->pt[i].change_x(xmax - l * (xmax - refX));

			}
		}
	}
	refX2 = refX1 + 0.2 * sin(time.currentTime() * 20);
	//std::cout << refX2 << "  " << refX1 << std::endl;
}