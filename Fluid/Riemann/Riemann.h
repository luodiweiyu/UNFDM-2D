#pragma once
#include"../../CoordTrans/coordTrans.h"
#include"../SuperSonic.h"
#include"../FluidVar/FluidFlux.h"
namespace SuperSonic
{
	namespace Riemann
	{
		FlowFlux HLLC_��(BaseVar& CL, BaseVar& CR, coordTrans& ct);//�������Ҳ��㣬����任�ο���
		FlowFlux HLLC_Y(BaseVar& CD, BaseVar& CU, coordTrans& ct);//�������Ҳ��㣬����任�ο���
	}
}
