#include "CollisionDetector.h"
#include "Vector2.h"


CollisionDetector::CollisionDetector(unsigned int staticObjects, unsigned int dynamicObjects, unsigned int freeObjects) :
	m_staticObjects(staticObjects),
	m_dynamicObjects(dynamicObjects),
	m_freeObject((staticObjects+ dynamicObjects +freeObjects) -1)
{
	m_CollisionIndices.circleCollision.reserve(m_staticObjects);
	m_CollisionIndices.aabbCollision.reserve(m_staticObjects);
	m_CollisionIndices.aabbCollision.reserve(m_staticObjects);
	m_CollisionIndices.MikowskiCollision.reserve(m_staticObjects);
}

CollisionDetector::CollisionDetector()
{
}


CollisionDetector::~CollisionDetector()
{
}

void CollisionDetector::CheckForCollisions(Object2D *objs)
{
	m_CollisionIndices.circleCollision.clear();
	m_CollisionIndices.aabbCollision.clear();
	m_CollisionIndices.aabbCollision.clear();
	m_CollisionIndices.MikowskiCollision.clear();

	CheckDynamicVsStatic(objs);
	CheckDynamicVsDynamic(objs);
	ChekcStaticDynamicVsFree(objs);
}

bool CollisionDetector::CircleCollision(CollisionData::Circle left, CollisionData::Circle right)
{
	float distance  = (left.center - right.center).Length();
	float sumRadien = left.radius + right.radius;
	return distance < sumRadien;
}

bool CollisionDetector::AABBCollision(CollisionData::AAB left , CollisionData::AAB right)
{
	Vector2 minLeft  = left.center - left.Halfbounds;
	Vector2 maxLeft  = left.center + left.Halfbounds;

	Vector2 minRight = right.center - right.Halfbounds;
	Vector2 maxRight = right.center + right.Halfbounds;

	return (minLeft.x <= maxRight.x) && (minLeft.y <= maxRight.y) && 
		   (maxLeft.x >= minRight.x) && (maxLeft.y >= minRight.y);
}

void CollisionDetector::CheckDynamicVsStatic(Object2D * objs)
{
	for (unsigned int i = m_staticObjects; i < (m_staticObjects + m_dynamicObjects); ++i)
	{
		for (unsigned j = 0; j < m_staticObjects; ++j)
		{
			if (CircleCollision(objs[i].GetCollisionData().c, objs[j].GetCollisionData().c))
			{
				if (AABBCollision(objs[i].GetCollisionData().aabb, objs[j].GetCollisionData().aabb))
				{
					m_CollisionIndices.aabbCollision.push_back(i);
					m_CollisionIndices.aabbCollision.push_back(j);
				}
				else
				{
					m_CollisionIndices.circleCollision.push_back(i);
					m_CollisionIndices.circleCollision.push_back(j);
				}
			}
		}
	}
}

void CollisionDetector::CheckDynamicVsDynamic(Object2D *objs)
{
	for (unsigned int i = m_staticObjects; i < (m_staticObjects+m_dynamicObjects); ++i)
	{
		for (unsigned j = (i+1); j < (m_staticObjects+m_dynamicObjects); ++j)
		{
			if (CircleCollision(objs[i].GetCollisionData().c, objs[j].GetCollisionData().c))
			{
				if (AABBCollision(objs[i].GetCollisionData().aabb, objs[j].GetCollisionData().aabb))
				{
					m_CollisionIndices.aabbCollision.push_back(i);
					m_CollisionIndices.aabbCollision.push_back(j);
				}
				else
				{
					m_CollisionIndices.circleCollision.push_back(i);
					m_CollisionIndices.circleCollision.push_back(j);
				}
			}
		}
	}
}

void CollisionDetector::ChekcStaticDynamicVsFree(Object2D *objs)
{
	for (unsigned int i = 0; i < (m_staticObjects + m_dynamicObjects); ++i)
	{
		if (CircleCollision(objs[i].GetCollisionData().c, objs[m_freeObject].GetCollisionData().c))
		{
			if (AABBCollision(objs[i].GetCollisionData().aabb, objs[m_freeObject].GetCollisionData().aabb))
			{
				m_CollisionIndices.aabbCollision.push_back(i);
				m_CollisionIndices.aabbCollision.push_back(m_freeObject);
			}
			else
			{
				m_CollisionIndices.circleCollision.push_back(i);
				m_CollisionIndices.circleCollision.push_back(m_freeObject);
			}
		}
	}
}
