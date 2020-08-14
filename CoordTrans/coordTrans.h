#pragma once
#include"../Geometry/point.h"
class coordTrans
{
	//transCof 是坐标转换系数
	//储存内容顺序为：xξ yξ zξ tξ,xη yη zη tη,xζ yζ zζ tζ, xτ yτ zτ tτ,
	//              ξx ηx ζx τx,ξy ηy ζy τy,ξz ηz ζz τz,ξt ηt ζt τt,
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
	double xξ() { return transCof[0]; };
	double yξ() { return transCof[1]; };
	double zξ() { return transCof[2]; };
	double tξ() { return transCof[3]; };

	double xη() { return transCof[4]; };
	double yη() { return transCof[5]; };
	double zη() { return transCof[6]; };
	double tη() { return transCof[7]; };

	double xζ() { return transCof[8]; };
	double yζ() { return transCof[9]; };
	double zζ() { return transCof[10]; };
	double tζ() { return transCof[11]; };

	double xτ() { return transCof[12]; };
	double yτ() { return transCof[13]; };
	double zτ() { return transCof[14]; };
	double tτ() { return transCof[15]; };

	double ξx() { return transCof[16]; };
	double ηx() { return transCof[17]; };
	double ζx() { return transCof[18]; };
	double τx() { return transCof[19]; };

	double ξy() { return transCof[20]; };
	double ηy() { return transCof[21]; };
	double ζy() { return transCof[22]; };
	double τy() { return transCof[23]; };

	double ξz() { return transCof[24]; };
	double ηz() { return transCof[25]; };
	double ζz() { return transCof[26]; };
	double τz() { return transCof[27]; };

	double ξt() { return transCof[28]; };
	double ηt() { return transCof[29]; };
	double ζt() { return transCof[30]; };
	double τt() { return transCof[31]; };

};

