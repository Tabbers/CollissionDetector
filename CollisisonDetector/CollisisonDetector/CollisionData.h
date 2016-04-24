#pragma once
#include "Triangle.h"

class CollisionData
{
	public:
		struct  OOBB
		{
		};

		struct  AAB
		{
			Vector2 center;
			Vector2 Halfbounds;
		};

		struct  Circle
		{
			Vector2 center;
			float radius;
		};
	public:
		Circle c;
		AAB    abb;
		OOBB   oobb;

		inline void GenerateDataFormTriangle(Triangle &tri, int fixup = 0)
		{
			c.center = tri.center;
			c.radius = tri.GetMaxDistance()+fixup;

			float minX = 5000;
			float minY = 5000;

			float maxX = 0;
			float maxY = 0;

			for (unsigned int i = 0; i < 3; ++i)
			{
				if (tri.points[i].x < minX)
					minX = tri.points[i].x;
				if (tri.points[i].y < minY)
					minY = tri.points[i].y;

				if (tri.points[i].x > maxX)
					maxX = tri.points[i].x;
				if (tri.points[i].y > maxY)
					maxY = tri.points[i].y;
			}
			
			Vector2 UpperRight(minX - fixup, minY - fixup);
			Vector2 LowerLeft(maxX + fixup,maxY + fixup);
			abb.center = tri.center;
			abb.Halfbounds = (LowerLeft - UpperRight)/2;

		};
};

