#pragma once
#include "Vector2.h"
#include "Randomizer.h"

struct Triangle
{
	Vector2 points[3];

	Vector2 center;

	inline void Generate(float limitX, float limitY)
	{
		float y1 = Randomizer::GetRandom(0,limitY/2 - limitY / 4);
		float y2 = Randomizer::GetRandom(y1 +limitY / 4, limitY - limitY / 4);

		float x1 = Randomizer::GetRandom(0, limitX / 3 - limitX / 4);
		float x2 = Randomizer::GetRandom(limitX * 2 / 3 + limitX /4, limitX );
		float x3 = Randomizer::GetRandom(limitX / 3 + limitX / 4, limitX * 2 / 3);


		points[0].x = x1;
		points[0].y = y1;

		points[1].x = x2;
		points[1].y = y1;

		points[2].x = x3;
		points[2].y = y2;

		center = Vector2((points[0].x + points[1].x + points[2].x) / 3, (points[0].y + points[1].y + points[2].y) / 3);
	
		points[0] = points[0] - center;
		points[1] = points[1] - center;
		points[2] = points[2] - center;

		center.x = 0;
		center.y = 0;
	};
	inline void Rotate(float angle)
	{
		for (unsigned int i = 0; i < 3; ++i)
		{
			points[i].rotate(angle);
		}
	}
	float GetMaxDistance()
	{
		float maxDistance = (points[0] - center).SqrLength();
		float distance;
		for (unsigned int i = 1; i < 3; ++i)
		{
			distance = (points[i] - center).SqrLength();
			if (distance > maxDistance) maxDistance = distance;
		}
		return sqrt(maxDistance);
	}
};