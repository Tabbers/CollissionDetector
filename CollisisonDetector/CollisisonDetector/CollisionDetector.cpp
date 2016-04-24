#include "CollisionDetector.h"
#include "Vector2.h"


CollisionDetector::CollisionDetector()
{
}


CollisionDetector::~CollisionDetector()
{
}

void CollisionDetector::CheckForCollisions(Object2D *)
{

}

bool CollisionDetector::CircleCollision(CollisionData::Circle left, CollisionData::Circle right)
{
	float distance  = (left.center - right.center).Length();
	float sumRadien = left.radius + right.radius;

	if (distance < sumRadien)
		return true;
	else
		return false;
	
	return false;
}

bool CollisionDetector::AABBCollision(CollisionData::AAB left , CollisionData::AAB right)
{
	Vector2 upperLeft;
	Vector2 lowerRight;


	// collision detected!
	

	return false;
}
