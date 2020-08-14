#pragma once
#include"../../Flowfield/mesh.h"
#include"../SuperSonic.h"
namespace SuperSonic
{
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
			BoundCondition() { bc = 0; };
			BoundCondition(Point& pt);
			void updateBC(const Point &pt);
			int bcType() { return bc; };
		};
	}
}
