#pragma once
#include"../../FluxBase/FluxBase.h"
#include"../FluidVar/FluidFlux.h"
#include"../../CoordTrans/coordTrans.h"
using namespace FluidFlux;
namespace Riemann
{
	FlowFlux HLLC_��(BaseVar& CL, BaseVar& CR, coordTrans& ct);//�������Ҳ��㣬����任�ο���
	FlowFlux HLLC_Y(BaseVar& CD, BaseVar& CU, coordTrans& ct);//�������Ҳ��㣬����任�ο���
}