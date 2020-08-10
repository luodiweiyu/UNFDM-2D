#pragma once
#include"../../Flowfield/mesh.h"
namespace Boundary
{
	const int notBc = 0;
	const int inlet = 1;
	const int outlet = 2;
	const int wall = 3;
	class BoundCondition
	{
	private:
		int bc;
	public:
		BoundCondition() {};
		BoundCondition(Point &pt);
		void updateBC(Point pt);
		int bcType() { return bc; };
	};
}