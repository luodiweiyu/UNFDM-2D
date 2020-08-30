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
	double S��, S��, c, u��, u��;
	double max�� = 0, max�� = 0;
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
				S�� = sqrt(localCT.��x() * localCT.��x() + localCT.��y() * localCT.��y());
				S�� = sqrt(localCT.��x() * localCT.��x() + localCT.��y() * localCT.��y());
				c = sqrt(gama * bv.p() / bv.rho());
				u�� = bv.u() * localCT.��x() + bv.v() * localCT.��y();
				u�� = bv.u() * localCT.��x() + bv.v() * localCT.��y();
				max�� = abs(u��) + c * S��;
				max�� = abs(u��) + c * S��;
				max1 = max(max1, max��);
				max2 = max(max2, max��);
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
				S�� = sqrt(localCT.��x() * localCT.��x() + localCT.��y() * localCT.��y());
				S�� = sqrt(localCT.��x() * localCT.��x() + localCT.��y() * localCT.��y());
				c = sqrt(gama * bv.p() / bv.rho());
				u�� = bv.u() * localCT.��x() + bv.v() * localCT.��y();
				u�� = bv.u() * localCT.��x() + bv.v() * localCT.��y();
				max�� = abs(u��) + c * S��;
				max�� = abs(u��) + c * S��;
				max1 = max(max1, max��);
				max2 = max(max2, max��);
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
	double S��, S��, c, u��, u��;
	double max�� = 0, max�� = 0;
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
				S�� = sqrt(localCT.��x() * localCT.��x() + localCT.��y() * localCT.��y());
				S�� = sqrt(localCT.��x() * localCT.��x() + localCT.��y() * localCT.��y());
				c = sqrt(g*bv.h());
				u�� = bv.u() * localCT.��x() + bv.v() * localCT.��y();
				u�� = bv.u() * localCT.��x() + bv.v() * localCT.��y();
				max�� = abs(u��) + c * S��;
				max�� = abs(u��) + c * S��;
				max1 = max(max1, max��);
				max2 = max(max2, max��);
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
				S�� = sqrt(localCT.��x() * localCT.��x() + localCT.��y() * localCT.��y());
				S�� = sqrt(localCT.��x() * localCT.��x() + localCT.��y() * localCT.��y());
				c = sqrt(g*bv.h());
				u�� = bv.u() * localCT.��x() + bv.v() * localCT.��y();
				u�� = bv.u() * localCT.��x() + bv.v() * localCT.��y();
				max�� = abs(u��) + c * S��;
				max�� = abs(u��) + c * S��;
				max1 = max(max1, max��);
				max2 = max(max2, max��);
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
//	double S��, S��, c, u��, u��;
//	double max�� = 0, max�� = 0;
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
//				S�� = sqrt(localCT.��x() * localCT.��x() + localCT.��y() * localCT.��y());
//				S�� = sqrt(localCT.��x() * localCT.��x() + localCT.��y() * localCT.��y());
//				c = sqrt(gama * bv.p() / bv.rho());
//				u�� = bv.u() * localCT.��x() + bv.v() * localCT.��y();
//				u�� = bv.u() * localCT.��x() + bv.v() * localCT.��y();
//				max�� = abs(u��) + c * S��;
//				max�� = abs(u��) + c * S��;
//				max1 = max(max1, max��);
//				max2 = max(max2, max��);
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
//				S�� = sqrt(localCT.��x() * localCT.��x() + localCT.��y() * localCT.��y());
//				S�� = sqrt(localCT.��x() * localCT.��x() + localCT.��y() * localCT.��y());
//				c = sqrt(gama * bv.p() / bv.rho());
//				u�� = bv.u() * localCT.��x() + bv.v() * localCT.��y();
//				u�� = bv.u() * localCT.��x() + bv.v() * localCT.��y();
//				max�� = abs(u��) + c * S��;
//				max�� = abs(u��) + c * S��;
//				max1 = max(max1, max��);
//				max2 = max(max2, max��);
//			}
//
//		}
//
//	}
//	dt = CFL / (max1 + max2);
//	if (tCurrent + dt > tEnd)
//		dt = tEnd - tCurrent;
//}

