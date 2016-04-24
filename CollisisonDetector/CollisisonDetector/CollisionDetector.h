#pragma once
#include "Object2D.h"
#include "CollisionData.h"
#include <vector>

class CollisionDetector
{
public:
	CollisionDetector();
	~CollisionDetector();
	void CheckForCollisions(Object2D*);
private:

	bool CircleCollision(CollisionData::Circle, CollisionData::Circle);
	bool AABBCollision(CollisionData::AAB, CollisionData::AAB);

	std::vector<int> circleCollision;
	std::vector<int> aabbCollision;
	std::vector<int> oobbCollision;
	std::vector<int> MikowskiCollision;
};

