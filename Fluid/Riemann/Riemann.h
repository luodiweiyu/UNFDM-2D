#pragma once
#include"../../FluxBase/FluxBase.h"
#include"../FluidVar/FluidFlux.h"
#include"../../CoordTrans/coordTrans.h"
using namespace FluidFlux;
namespace Riemann
{
	FlowFlux HLLC_Χ(BaseVar& CL, BaseVar& CR, coordTrans& ct);//半点左侧右侧格点，坐标变换参考点
	FlowFlux HLLC_Y(BaseVar& CD, BaseVar& CU, coordTrans& ct);//半点左侧右侧格点，坐标变换参考点
}