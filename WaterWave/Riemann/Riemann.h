#pragma once
#include"../WaterWave.h"
#include"../WaterWaveVar/WaterWaveVar.h"
#include"../../CoordTrans/coordTrans.h"

namespace WaterWave
 {
	namespace Riemann
	{
		FlowFlux Direct_¦¶(BaseVar& CL, BaseVar& CR);
		FlowFlux Direct_Y(BaseVar& CD, BaseVar& CU);
		FlowFlux Direct_¦Î(BaseVar& CL, BaseVar& CR, coordTrans& ct);
		FlowFlux Direct_¦Ç(BaseVar& CD, BaseVar& CU, coordTrans& ct);

	}
}
