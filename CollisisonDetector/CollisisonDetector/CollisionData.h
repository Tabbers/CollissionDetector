#pragma once
#include "Triangle.h"
#include "Randomizer.h"

class CollisionData
{
	public:
		struct  OOBB
		{
			Vector2 ul;
			Vector2 ur;
			Vector2 dr;
			Vector2 dl;
		};

		struct  AABB
		{
			Vector2 ul;
			Vector2 dr;
		};

		struct  Circle
		{
			Vector2 center;
			float radius;
		};
	public:
		Circle c;
		AABB   aabb;
		OOBB   oobb;

		inline void Rotate(float angle)
		{
			aabb.ul.rotate(angle);
			aabb.dr.rotate(angle);

			oobb.ul.rotate(angle);
			oobb.ur.rotate(angle);
			oobb.dr.rotate(angle);
			oobb.dl.rotate(angle);
		}
		inline void GenerateDataFormTriangle(Triangle &tri, int fixup = 0)
		{
			//Circle
			c.center = tri.center;
			c.radius = tri.GetMaxDistance()+fixup;
			
			//OOBB
			
			oobb.ul = tri.points[0];
			oobb.ur = tri.points[1];

			oobb.dl = { tri.points[0].x, tri.points[2].y };
			oobb.dr = { tri.points[1].x , tri.points[2].y };

			float rotation = Randomizer::GetRandom(0.f, 360.0f);

			oobb.ul.rotate(rotation);
			oobb.ur.rotate(rotation);
			oobb.dr.rotate(rotation);
			oobb.dl.rotate(rotation);

			tri.Rotate(rotation);

			//AABB
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

			Vector2 ul(minX - fixup, minY - fixup);
			Vector2 dr(maxX + fixup, maxY + fixup);

			aabb.ul = ul;
			aabb.dr = dr;
		};
};

