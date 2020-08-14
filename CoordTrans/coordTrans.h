#pragma once
#include"../Geometry/point.h"
class coordTrans
{
	//transCof ������ת��ϵ��
	//��������˳��Ϊ��x�� y�� z�� t��,x�� y�� z�� t��,x�� y�� z�� t��, x�� y�� z�� t��,
	//              ��x ��x ��x ��x,��y ��y ��y ��y,��z ��z ��z ��z,��t ��t ��t ��t,
private:
	double transCof[32];
	double jacob;
public:
	coordTrans() { jacob = 0; };
	coordTrans(double dt,Point tRight, Point tLeft, Point xRight, Point xLeft, Point yRight, Point yLeft, Point zRight = Point(0, 0), Point zLeft = Point(0, 0));
	coordTrans(Point xRight, Point xLeft, Point yRight, Point yLeft, Point zRight = Point(0, 0), Point zLeft = Point(0, 0));
	void updCofNoTime(Point xRight, Point xLeft, Point yRight, Point yLeft, Point zRight = Point(0, 0), Point zLeft = Point(0, 0));
	void updCofTime(double dt, Point tRight, Point tLeft);
	void updJacob();
	double J() { return jacob; };
	double x��() { return transCof[0]; };
	double y��() { return transCof[1]; };
	double z��() { return transCof[2]; };
	double t��() { return transCof[3]; };

	double x��() { return transCof[4]; };
	double y��() { return transCof[5]; };
	double z��() { return transCof[6]; };
	double t��() { return transCof[7]; };

	double x��() { return transCof[8]; };
	double y��() { return transCof[9]; };
	double z��() { return transCof[10]; };
	double t��() { return transCof[11]; };

	double x��() { return transCof[12]; };
	double y��() { return transCof[13]; };
	double z��() { return transCof[14]; };
	double t��() { return transCof[15]; };

	double ��x() { return transCof[16]; };
	double ��x() { return transCof[17]; };
	double ��x() { return transCof[18]; };
	double ��x() { return transCof[19]; };

	double ��y() { return transCof[20]; };
	double ��y() { return transCof[21]; };
	double ��y() { return transCof[22]; };
	double ��y() { return transCof[23]; };

	double ��z() { return transCof[24]; };
	double ��z() { return transCof[25]; };
	double ��z() { return transCof[26]; };
	double ��z() { return transCof[27]; };

	double ��t() { return transCof[28]; };
	double ��t() { return transCof[29]; };
	double ��t() { return transCof[30]; };
	double ��t() { return transCof[31]; };

};

