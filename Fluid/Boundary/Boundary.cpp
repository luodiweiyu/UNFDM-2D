#include"Boundary.h"
#include"../../Flowfield/flowfield.h"
using namespace Boundary;
BoundCondition::BoundCondition(Point& pt)
{
	updateBC(pt);
}

void BoundCondition::updateBC(Point pt)
{
	if (abs(pt.x() - xmin) <= delta)
		bc = inlet;
	else if (abs(pt.x() - xmax) <= delta)
		bc = outlet;
	else if (abs(pt.y() - ymin) <= delta)
		bc = outlet;
	else if (abs(pt.y() - ymax) <= delta)
		bc = outlet;
	else
		bc = notBc;
}
