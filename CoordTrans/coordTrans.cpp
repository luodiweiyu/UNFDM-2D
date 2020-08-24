#include "coordTrans.h"
void coordTrans::updJacob()
{
	//J
	jacob = x��() * (y��() * z��() - y��() * z��())
		- x��() * (y��() * z��() - y��() * z��())
		+ x��() * (y��() * z��() - y��() * z��());
	jacob = 1.0 / jacob;
}

void coordTrans::updCofTime(double dt, Point tRight, Point tLeft)
{
	//x�� y�� z�� t��,
	transCof[12] = (tRight.x() - tLeft.x()) / dt;
	transCof[13] = (tRight.y() - tLeft.y()) / dt;
	transCof[14] = (tRight.z() - tLeft.z()) / dt;
	transCof[15] = 1;
	//��t ��t ��t ��t,
	transCof[28] = -(x��() * ��x() + y��() * ��y() + z��() * ��z());
	transCof[29] = -(x��() * ��x() + y��() * ��y() + z��() * ��z());
	transCof[30] = -(x��() * ��x() + y��() * ��y() + z��() * ��z());
	transCof[31] = 1;
}
void coordTrans::updCofNoTime(Point xRight, Point xLeft, Point yRight, Point yLeft, Point zRight, Point zLeft)
{
	//x�� y�� z�� t��
	transCof[0] = 0.5 * (xRight.x() - xLeft.x());
	transCof[1] = 0.5 * (xRight.y() - xLeft.y());
	transCof[2] = 0.5 * (xRight.z() - xLeft.z());
	transCof[3] = 0;

	//x�� y�� z�� t��,
	transCof[4] = 0.5 * (yRight.x() - yLeft.x());
	transCof[5] = 0.5 * (yRight.y() - yLeft.y());
	transCof[6] = 0.5 * (yRight.z() - yLeft.z());
	transCof[7] = 0;

	//x�� y�� z�� t��,
	transCof[8] = 0.5 * (zRight.x() - zLeft.x());
	transCof[9] = 0.5 * (zRight.y() - zLeft.y());
	transCof[10] = 1;
	transCof[11] = 0;
	//x�� y�� z�� t��,
	transCof[12] = 0;
	transCof[13] = 0;
	transCof[14] = 0;
	transCof[15] = 1;

	updJacob();
	//��x ��x ��x ��x,
	transCof[16] = jacob * (y��() * z��() - y��() * z��());
	transCof[17] = jacob * (y��() * z��() - y��() * z��());
	transCof[18] = jacob * (y��() * z��() - y��() * z��());
	transCof[19] = 0;

	//��y ��y ��y ��y,
	transCof[20] = jacob * (x��() * z��() - x��() * z��());
	transCof[21] = jacob * (x��() * z��() - x��() * z��());
	transCof[22] = jacob * (x��() * z��() - x��() * z��());
	transCof[23] = 0;

	//��z ��z ��z ��z,
	transCof[24] = jacob * (x��() * y��() - x��() * y��());
	transCof[25] = jacob * (x��() * y��() - x��() * y��());
	transCof[26] = jacob * (x��() * y��() - x��() * y��());
	transCof[27] = 0;
	//��t ��t ��t ��t,
	transCof[28] = -(x��() * ��x() + y��() * ��y() + z��() * ��z());
	transCof[29] = -(x��() * ��x() + y��() * ��y() + z��() * ��z());
	transCof[30] = -(x��() * ��x() + y��() * ��y() + z��() * ��z());
	transCof[31] = 1;
}
coordTrans::coordTrans(double dt, Point tRight, Point tLeft, Point xRight, Point xLeft, Point yRight, Point yLeft, Point zRight, Point zLeft)
{
	updCofNoTime(xRight, xLeft, yRight, yLeft, zRight, zLeft);
	updCofTime(dt, tRight, tLeft);
}
coordTrans::coordTrans(Point xRight, Point xLeft, Point yRight, Point yLeft, Point zRight, Point zLeft)
{
	updCofNoTime(xRight, xLeft, yRight, yLeft, zRight, zLeft);
}