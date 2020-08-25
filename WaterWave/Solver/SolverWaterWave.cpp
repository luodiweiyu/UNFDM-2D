#include<iostream>
#include<fstream>
#include"SolverWaterWave.h"
#include"../../CoordTrans/coordTrans.h"
#include"../Riemann/Riemann.h"
namespace WaterWave
{
	void Solver::init()
	{
		int i;
		for (i = 0; i < size; i++)
		{
			if (mh->point(i).x() <= 1)
			{
				bv[i].changeBV(10, 0, 0);
				cv[i].updateFromBaseVar(bv[i]);
			}
			else
			{
				bv[i].changeBV(5, 0, 0);
				cv[i].updateFromBaseVar(bv[i]);
			}
		}
	}
	void Solver::updateBC(Mesh& mh)
	{
		int i;
		for (i = 0; i < mh.ptNum(); i++)
			bc[i].updateBC(mh.point(i));
	}
	void Solver::updateBounVar()
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
				bv[i].changeBV(10, 0, 0);

			//bv[i].changeBV(5, 4.1749, 0, 4);
			else
			{
				neiborNum = mh->point(i).neibornum();
				bvTemp.changeBV(0, 0, 0);
				num = 0;
				if (neiborNum == 2)
				{
					for (j = 0; j < neiborNum; j++)
					{
						id = mh->point(i).getneibor(j).id();
						bvTemp.changeBV(bvTemp.h() + bv[id].h(),
							bvTemp.u() + bv[id].u(),
							bvTemp.v() + bv[id].v());
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
							bvTemp.changeBV(bvTemp.h() + bv[id].h(),
								bvTemp.u() + bv[id].u(),
								bvTemp.v() + bv[id].v());
							num++;
						}
					}
				}
				bv[i].changeBV(bvTemp.h() / num, bvTemp.u() / num, bvTemp.v() / num);
			}
		}
	}
	void Solver::updateBaseVar()
	{
		int i;
		for (i = 0; i < size; i++)
			bv[i].updateFromConsVar(cv[i]);
	}
	FlowFlux WaterWave::solverFourNeibor(Point* localPoint, WaterWave::BaseVar* localBV, Point* neiborPoint, WaterWave::BaseVar* neiborBV)
	{
		using namespace Riemann;
		coordTrans localCT(neiborPoint[0], neiborPoint[2], neiborPoint[1], neiborPoint[3]);
		//FlowFlux F1 = Direct_ξ(neiborBV[2], *localBV, localCT);
		//FlowFlux F2 = Direct_ξ(*localBV, neiborBV[0], localCT);
		//FlowFlux G1 = Direct_η(neiborBV[3], *localBV, localCT);
		//FlowFlux G2 = Direct_η(*localBV, neiborBV[1], localCT);
		//FlowFlux localFF = F2 - F1 + G2 - G1;

		FlowFlux fLocalPlus = StegerWarming(*localBV, localCT, "xi", "plus");
		FlowFlux fLocalMinus = StegerWarming(*localBV, localCT, "xi", "minus");
		FlowFlux fLeftPlus = StegerWarming(neiborBV[2], localCT, "xi", "plus");
		FlowFlux fRightMinus = StegerWarming(neiborBV[0], localCT, "xi", "minus");
		FlowFlux gLocalPlus = StegerWarming(*localBV, localCT, "eta", "plus");
		FlowFlux gLocalMinus = StegerWarming(*localBV, localCT, "eta", "minus");
		FlowFlux gDownPlus = StegerWarming(neiborBV[3], localCT, "eta", "plus");
		FlowFlux gUpMinus = StegerWarming(neiborBV[1], localCT, "eta", "minus");
		FlowFlux localFF =  (fLocalPlus - fLeftPlus + fRightMinus - fLocalMinus + gLocalPlus - gDownPlus + gUpMinus - gLocalMinus)/**localCT.J()*/;
		return localFF;
	}
	FlowFlux WaterWave::solverThreeNeibor(Point* localPoint, BaseVar* localBV, Point* neiborPoint, BaseVar* neiborBV)
	{
		int i, n0, n1, n2, n3;
		Point neiborPoint_4[4];
		BaseVar neiborBV_4[4];
		FlowFlux localFF;
		localFF.changeFF(0, 0, 0);
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
			localFF =localFF+ solverFourNeibor(localPoint, localBV, neiborPoint_4, neiborBV_4);
			//std::cout << localFF.flux(0) << " " << localFF.flux(1) << " " << localFF.flux(2) << " " << localFF.flux(3) << std::endl;
		}
		localFF = localFF / 12;
		//std::cout << localFF.flux(0) << " " << localFF.flux(1) << " " << localFF.flux(2) << " " << localFF.flux(3) << std::endl;
		return localFF;
	}

	void Solver::solverCore()
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
 				localFF = solverThreeNeibor(&mh->point(i), &bv[i], neiborPoint, neiborBV);
			}
			else
			{
				for (j = 0; j < mh->point(i).neibornum(); j++)
				{
					neiborid = mh->point(i).getneibor(j).id();
					neiborPoint[j] = mh->point(neiborid);
					neiborBV[j] = bv[neiborid];
				}
				localFF = solverFourNeibor(&mh->point(i), &bv[i], neiborPoint, neiborBV);
			}
			cv[i] =cv[i]+ localFF * (-time.deltaT());
		}
	}


	void Solver::solver()
	{
		time.init();
		init();
		outFlow("mesh.dat");
		int count = 0;
		while (time.currentTime() < time.endTime())
		{
			//time.update(*bv, *mh);
			time.update(1e-4);
			solverCore();
			updateBaseVar();
			updateBounVar();
			if (count % 1 == 0)
			{
				outFlow("data/t=" + std::to_string(time.currentTime()) + ".dat");
				std::cout << "step = " << count << "  time = " << time.currentTime() << std::endl;
			}
			count++;
			time.updateTCurrent();
		}
	}


	void Solver::outFlow(string filename)
	{
		using std::ofstream;
		using std::endl;
		int i;
		int face_num = 0;
		for (i = 0; i < mh->pyNum(); i++)
			face_num += mh->poly(i).ln_num();

		ofstream fout(filename);
		fout << "variables = x,y,h,u,v" << endl;
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
			fout << bv[i].h() << "  ";
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

}
