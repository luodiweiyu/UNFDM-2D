#include "Time.h"
#include"../CoordTrans/coordTrans.h"
#include"../Math/math.h"
Time::Time(double tStart_ , double tEnd_, double CFL_ )
{
	init(tStart_, tEnd_, CFL_);
}
void Time::init(double tStart_, double tEnd_, double CFL_)
{
	tStart = tStart_;
	tEnd = tEnd_;
	CFL = CFL_;
	tCurrent = tStart;
}

void Time::update(SuperSonic::BaseVar& bv, Mesh& mh)
{
	using namespace SuperSonic;
	int i, j, neiborid;
	int n0, n1, n2, n3;
	Point neiborPoint[4];
	Point neiborPoint_4[4];
	double max1 = 0, max2 = 0;
	double S¦Î, S¦Ç, c, u¦Î, u¦Ç;
	double max¦Î = 0, max¦Ç = 0;
	for (i = 0; i < mh.ptNum(); i++)
	{
		if (mh.point(i).neibornum() == 3)
		{
			for (j = 0; j < mh.point(i).neibornum(); j++)
			{
				neiborid = mh.point(i).getneibor(j).id();
				neiborPoint[j] = mh.point(neiborid);
			}
			for (j = 0; j < 12; j++)
			{
				n0 = ThreeNeiborMethod[j][0];
				n1 = ThreeNeiborMethod[j][1];
				n2 = ThreeNeiborMethod[j][2];
				n3 = ThreeNeiborMethod[j][3];
				neiborPoint_4[0] = neiborPoint[n0];
				neiborPoint_4[1] = neiborPoint[n1];
				neiborPoint_4[2] = neiborPoint[n2];
				neiborPoint_4[3] = neiborPoint[n3];
				coordTrans localCT(dt, mh.point(i), mh.point(i), neiborPoint_4[0], neiborPoint_4[2], neiborPoint_4[1], neiborPoint_4[3]);
				S¦Î = sqrt(localCT.¦Îx() * localCT.¦Îx() + localCT.¦Îy() * localCT.¦Îy());
				S¦Ç = sqrt(localCT.¦Çx() * localCT.¦Çx() + localCT.¦Çy() * localCT.¦Çy());
				c = sqrt(gama * bv.p() / bv.rho());
				u¦Î = bv.u() * localCT.¦Îx() + bv.v() * localCT.¦Îy();
				u¦Ç = bv.u() * localCT.¦Çx() + bv.v() * localCT.¦Çy();
				max¦Î = abs(u¦Î) + c * S¦Î;
				max¦Ç = abs(u¦Î) + c * S¦Ç;
				max1 = max(max1, max¦Î);
				max2 = max(max2, max¦Ç);
			}

		}
		else if (mh.point(i).neibornum() == 4)
		{
			for (j = 0; j < mh.point(i).neibornum(); j++)
			{
				neiborid = mh.point(i).getneibor(j).id();
				neiborPoint[j] = mh.point(neiborid);
			}
			for (j = 0; j < 12; j++)
			{
				coordTrans localCT(dt, mh.point(i), mh.point(i), neiborPoint[0], neiborPoint[2], neiborPoint[1], neiborPoint[3]);
				S¦Î = sqrt(localCT.¦Îx() * localCT.¦Îx() + localCT.¦Îy() * localCT.¦Îy());
				S¦Ç = sqrt(localCT.¦Çx() * localCT.¦Çx() + localCT.¦Çy() * localCT.¦Çy());
				c = sqrt(gama * bv.p() / bv.rho());
				u¦Î = bv.u() * localCT.¦Îx() + bv.v() * localCT.¦Îy();
				u¦Ç = bv.u() * localCT.¦Çx() + bv.v() * localCT.¦Çy();
				max¦Î = abs(u¦Î) + c * S¦Î;
				max¦Ç = abs(u¦Î) + c * S¦Ç;
				max1 = max(max1, max¦Î);
				max2 = max(max2, max¦Ç);
			}

		}

	}
	dt = CFL / (max1 + max2);
	if (tCurrent + dt > tEnd)
		dt = tEnd - tCurrent;
}
void Time::update(WaterWave::BaseVar& bv, Mesh& mh)
{
	using namespace WaterWave;
	int i, j, neiborid;
	int n0, n1, n2, n3;
	Point neiborPoint[4];
	Point neiborPoint_4[4];
	double max1 = 0, max2 = 0;
	double S¦Î, S¦Ç, c, u¦Î, u¦Ç;
	double max¦Î = 0, max¦Ç = 0;
	for (i = 0; i < mh.ptNum(); i++)
	{
		if (mh.point(i).neibornum() == 3)
		{
			for (j = 0; j < mh.point(i).neibornum(); j++)
			{
				neiborid = mh.point(i).getneibor(j).id();
				neiborPoint[j] = mh.point(neiborid);
			}
			for (j = 0; j < 12; j++)
			{
				n0 = ThreeNeiborMethod[j][0];
				n1 = ThreeNeiborMethod[j][1];
				n2 = ThreeNeiborMethod[j][2];
				n3 = ThreeNeiborMethod[j][3];
				neiborPoint_4[0] = neiborPoint[n0];
				neiborPoint_4[1] = neiborPoint[n1];
				neiborPoint_4[2] = neiborPoint[n2];
				neiborPoint_4[3] = neiborPoint[n3];
				coordTrans localCT(dt, mh.point(i), mh.point(i), neiborPoint_4[0], neiborPoint_4[2], neiborPoint_4[1], neiborPoint_4[3]);
				S¦Î = sqrt(localCT.¦Îx() * localCT.¦Îx() + localCT.¦Îy() * localCT.¦Îy());
				S¦Ç = sqrt(localCT.¦Çx() * localCT.¦Çx() + localCT.¦Çy() * localCT.¦Çy());
				c = sqrt(g*bv.h());
				u¦Î = bv.u() * localCT.¦Îx() + bv.v() * localCT.¦Îy();
				u¦Ç = bv.u() * localCT.¦Çx() + bv.v() * localCT.¦Çy();
				max¦Î = abs(u¦Î) + c * S¦Î;
				max¦Ç = abs(u¦Î) + c * S¦Ç;
				max1 = max(max1, max¦Î);
				max2 = max(max2, max¦Ç);
			}
		}
		else if (mh.point(i).neibornum() == 4)
		{
			for (j = 0; j < mh.point(i).neibornum(); j++)
			{
				neiborid = mh.point(i).getneibor(j).id();
				neiborPoint[j] = mh.point(neiborid);
			}
			for (j = 0; j < 12; j++)
			{
				coordTrans localCT(dt, mh.point(i), mh.point(i), neiborPoint[0], neiborPoint[2], neiborPoint[1], neiborPoint[3]);
				S¦Î = sqrt(localCT.¦Îx() * localCT.¦Îx() + localCT.¦Îy() * localCT.¦Îy());
				S¦Ç = sqrt(localCT.¦Çx() * localCT.¦Çx() + localCT.¦Çy() * localCT.¦Çy());
				c = sqrt(g*bv.h());
				u¦Î = bv.u() * localCT.¦Îx() + bv.v() * localCT.¦Îy();
				u¦Ç = bv.u() * localCT.¦Çx() + bv.v() * localCT.¦Çy();
				max¦Î = abs(u¦Î) + c * S¦Î;
				max¦Ç = abs(u¦Î) + c * S¦Ç;
				max1 = max(max1, max¦Î);
				max2 = max(max2, max¦Ç);
			}

		}

	}
	dt = CFL / (max1 + max2);
	if (tCurrent + dt > tEnd)
		dt = tEnd - tCurrent;
}

//void Time::update(WaterWave::BaseVar& bv, Mesh& mh)
//{
//	using namespace WaterWave;
//	int i, j, neiborid;
//	int n0, n1, n2, n3;
//	Point neiborPoint[4];
//	Point neiborPoint_4[4];
//	double max1 = 0, max2 = 0;
//	double S¦Î, S¦Ç, c, u¦Î, u¦Ç;
//	double max¦Î = 0, max¦Ç = 0;
//	for (i = 0; i < mh.ptNum(); i++)
//	{
//		if (mh.point(i).neibornum() == 3)
//		{
//			for (j = 0; j < mh.point(i).neibornum(); j++)
//			{
//				neiborid = mh.point(i).getneibor(j).id();
//				neiborPoint[j] = mh.point(neiborid);
//			}
//			for (j = 0; j < 12; j++)
//			{
//				n0 = ThreeNeiborMethod[j][0];
//				n1 = ThreeNeiborMethod[j][1];
//				n2 = ThreeNeiborMethod[j][2];
//				n3 = ThreeNeiborMethod[j][3];
//				neiborPoint_4[0] = neiborPoint[n0];
//				neiborPoint_4[1] = neiborPoint[n1];
//				neiborPoint_4[2] = neiborPoint[n2];
//				neiborPoint_4[3] = neiborPoint[n3];
//				coordTrans localCT(dt, mh.point(i), mh.point(i), neiborPoint_4[0], neiborPoint_4[2], neiborPoint_4[1], neiborPoint_4[3]);
//				S¦Î = sqrt(localCT.¦Îx() * localCT.¦Îx() + localCT.¦Îy() * localCT.¦Îy());
//				S¦Ç = sqrt(localCT.¦Çx() * localCT.¦Çx() + localCT.¦Çy() * localCT.¦Çy());
//				c = sqrt(gama * bv.p() / bv.rho());
//				u¦Î = bv.u() * localCT.¦Îx() + bv.v() * localCT.¦Îy();
//				u¦Ç = bv.u() * localCT.¦Çx() + bv.v() * localCT.¦Çy();
//				max¦Î = abs(u¦Î) + c * S¦Î;
//				max¦Ç = abs(u¦Î) + c * S¦Ç;
//				max1 = max(max1, max¦Î);
//				max2 = max(max2, max¦Ç);
//			}
//
//		}
//		else if (mh.point(i).neibornum() == 4)
//		{
//			for (j = 0; j < mh.point(i).neibornum(); j++)
//			{
//				neiborid = mh.point(i).getneibor(j).id();
//				neiborPoint[j] = mh.point(neiborid);
//			}
//			for (j = 0; j < 12; j++)
//			{
//				coordTrans localCT(dt, mh.point(i), mh.point(i), neiborPoint[0], neiborPoint[2], neiborPoint[1], neiborPoint[3]);
//				S¦Î = sqrt(localCT.¦Îx() * localCT.¦Îx() + localCT.¦Îy() * localCT.¦Îy());
//				S¦Ç = sqrt(localCT.¦Çx() * localCT.¦Çx() + localCT.¦Çy() * localCT.¦Çy());
//				c = sqrt(gama * bv.p() / bv.rho());
//				u¦Î = bv.u() * localCT.¦Îx() + bv.v() * localCT.¦Îy();
//				u¦Ç = bv.u() * localCT.¦Çx() + bv.v() * localCT.¦Çy();
//				max¦Î = abs(u¦Î) + c * S¦Î;
//				max¦Ç = abs(u¦Î) + c * S¦Ç;
//				max1 = max(max1, max¦Î);
//				max2 = max(max2, max¦Ç);
//			}
//
//		}
//
//	}
//	dt = CFL / (max1 + max2);
//	if (tCurrent + dt > tEnd)
//		dt = tEnd - tCurrent;
//}

