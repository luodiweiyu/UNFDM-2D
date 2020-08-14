#pragma once
#include"../WaterWave.h"
#include"../../Geometry/point.h"
 namespace WaterWave 
 {
	 namespace Boundary
	 {
		 class BoundCondition
		 {
		 private:
			 int bc;
		 public:
			 BoundCondition() { bc = 0; };
			 BoundCondition(Point& pt);
			 void updateBC(const Point& pt);
			 int bcType() { return bc; };
		 };
}
}
