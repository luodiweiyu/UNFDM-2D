#include "coordTrans.h"
void coordTrans::updJacob()
{
	//J
	jacob = x¦Î() * (y¦Ç() * z¦Æ() - y¦Æ() * z¦Ç())
		- x¦Ç() * (y¦Î() * z¦Æ() - y¦Æ() * z¦Î())
		+ x¦Æ() * (y¦Î() * z¦Ç() - y¦Ç() * z¦Î());
	jacob = 1.0 / jacob;
}

void coordTrans::updCofTime(double dt, Point tRight, Point tLeft)
{
	//x¦Ó y¦Ó z¦Ó t¦Ó,
	transCof[12] = (tRight.x() - tLeft.x()) / dt;
	transCof[13] = (tRight.y() - tLeft.y()) / dt;
	transCof[14] = (tRight.z() - tLeft.z()) / dt;
	transCof[15] = 1;
	//¦Ît ¦Çt ¦Æt ¦Ót,
	transCof[28] = -(x¦Ó() * ¦Îx() + y¦Ó() * ¦Îy() + z¦Ó() * ¦Îz());
	transCof[29] = -(x¦Ó() * ¦Çx() + y¦Ó() * ¦Çy() + z¦Ó() * ¦Çz());
	transCof[30] = -(x¦Ó() * ¦Æx() + y¦Ó() * ¦Æy() + z¦Ó() * ¦Æz());
	transCof[31] = 1;
}
void coordTrans::updCofNoTime(Point xRight, Point xLeft, Point yRight, Point yLeft, Point zRight, Point zLeft)
{
	//x¦Î y¦Î z¦Î t¦Î
	transCof[0] = 0.5 * (xRight.x() - xLeft.x());
	transCof[1] = 0.5 * (xRight.y() - xLeft.y());
	transCof[2] = 0.5 * (xRight.z() - xLeft.z());
	transCof[3] = 0;

	//x¦Ç y¦Ç z¦Ç t¦Ç,
	transCof[4] = 0.5 * (yRight.x() - yLeft.x());
	transCof[5] = 0.5 * (yRight.y() - yLeft.y());
	transCof[6] = 0.5 * (yRight.z() - yLeft.z());
	transCof[7] = 0;

	//x¦Æ y¦Æ z¦Æ t¦Æ,
	transCof[8] = 0.5 * (zRight.x() - zLeft.x());
	transCof[9] = 0.5 * (zRight.y() - zLeft.y());
	transCof[10] = 1;
	transCof[11] = 0;
	//x¦Ó y¦Ó z¦Ó t¦Ó,
	transCof[12] = 0;
	transCof[13] = 0;
	transCof[14] = 0;
	transCof[15] = 1;

	updJacob();
	//¦Îx ¦Çx ¦Æx ¦Óx,
	transCof[16] = jacob * (y¦Ç() * z¦Æ() - y¦Æ() * z¦Ç());
	transCof[17] = jacob * (y¦Æ() * z¦Î() - y¦Î() * z¦Æ());
	transCof[18] = jacob * (y¦Î() * z¦Ç() - y¦Ç() * z¦Î());
	transCof[19] = 0;

	//¦Îy ¦Çy ¦Æy ¦Óy,
	transCof[20] = jacob * (x¦Æ() * z¦Ç() - x¦Ç() * z¦Æ());
	transCof[21] = jacob * (x¦Î() * z¦Æ() - x¦Æ() * z¦Î());
	transCof[22] = jacob * (x¦Ç() * z¦Î() - x¦Î() * z¦Ç());
	transCof[23] = 0;

	//¦Îz ¦Çz ¦Æz ¦Óz,
	transCof[24] = jacob * (x¦Ç() * y¦Æ() - x¦Æ() * y¦Ç());
	transCof[25] = jacob * (x¦Æ() * y¦Î() - x¦Î() * y¦Æ());
	transCof[26] = jacob * (x¦Î() * y¦Ç() - x¦Ç() * y¦Î());
	transCof[27] = 0;
	//¦Ît ¦Çt ¦Æt ¦Ót,
	transCof[28] = -(x¦Ó() * ¦Îx() + y¦Ó() * ¦Îy() + z¦Ó() * ¦Îz());
	transCof[29] = -(x¦Ó() * ¦Çx() + y¦Ó() * ¦Çy() + z¦Ó() * ¦Çz());
	transCof[30] = -(x¦Ó() * ¦Æx() + y¦Ó() * ¦Æy() + z¦Ó() * ¦Æz());
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