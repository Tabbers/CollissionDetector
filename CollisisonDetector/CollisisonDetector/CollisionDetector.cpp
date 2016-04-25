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
	m_CollisionIndices.oobbCollision.clear();
	m_CollisionIndices.MikowskiCollision.clear();

	CheckDynamicVsStatic(objs);
	CheckDynamicVsDynamic(objs);
	ChekcStaticDynamicVsFree(objs);
}

bool CollisionDetector::CircleCollision(CollisionData::Circle &left, CollisionData::Circle &right)
{
	float distance  = (left.center - right.center).Length();
	float sumRadien = left.radius + right.radius;
	return distance < sumRadien;
}

bool CollisionDetector::AABBCollision(CollisionData::AABB &left , CollisionData::AABB &right, Vector2 posl, Vector2 posr)
{
	Vector2 minleft  = posl + left.ul;
	Vector2 maxleft  = posl + left.dr;
	Vector2 minRight = posr + right.ul;
	Vector2 maxRight = posr + right.dr;
	return minRight > maxleft && maxRight < minleft;
}

bool CollisionDetector::OOBBCollision(CollisionData::OOBB &left, CollisionData::OOBB &right, Vector2 posl, Vector2 posr)
{
	CollisionData::OOBB leftHelper;
	leftHelper.ul = posl + left.ul;
	leftHelper.ur = posl + left.ur;
	leftHelper.dr = posl + left.dr;
	leftHelper.dl = posl + left.dl;
	CollisionData::OOBB rightHelper;
	rightHelper.ul = posr + right.ul;
	rightHelper.ur = posr + right.ur;
	rightHelper.dr = posr + right.dr;
	rightHelper.dl = posr + right.dl;

	return OOBCollisionSingleObject(leftHelper,rightHelper) && OOBCollisionSingleObject(rightHelper, leftHelper);
}

bool CollisionDetector::OOBCollisionSingleObject(CollisionData::OOBB &left, CollisionData::OOBB &right)
{
	Vector2 axisX = (left.dl - left.dr).Normalize();
	Vector2 axisY = (left.dl - left.ul).Normalize();

	Vector2 extents = { (left.dl - left.dr).Length(),(left.dl - left.ul).Length() };

	Vector2 rightul = right.ul - left.dl;
	Vector2 rightur = right.ur - left.dl;
	Vector2 rightdr = right.dr - left.dl;
	Vector2 rightdl = right.dl - left.dl;

	float projectedLengthUl = rightul.dot(axisX);
	float projectedLengthUr = rightur.dot(axisX);
	float projectedLengthDr = rightdr.dot(axisX);
	float projectedLengthDl = rightdl.dot(axisX);

	if (projectedLengthUl > extents.x &&
		projectedLengthUr > extents.x &&
		projectedLengthDr > extents.x &&
		projectedLengthDl > extents.x)
		return false;

	projectedLengthUl = rightul.dot(axisY);
	projectedLengthUr = rightur.dot(axisY);
	projectedLengthDr = rightdr.dot(axisY);
	projectedLengthDl = rightdl.dot(axisY);

	if (projectedLengthUl > extents.y &&
		projectedLengthUr > extents.y &&
		projectedLengthDr > extents.y &&
		projectedLengthDl > extents.y)
		return false;

	return true;
}

void CollisionDetector::CheckDynamicVsStatic(Object2D * objs)
{
	for (unsigned int i = m_staticObjects; i < (m_staticObjects + m_dynamicObjects); ++i)
	{
		for (unsigned j = 0; j < m_staticObjects; ++j)
		{
			if (CircleCollision(objs[i].GetCollisionData().c, objs[j].GetCollisionData().c))
			{
				if (AABBCollision(objs[i].GetCollisionData().aabb, objs[j].GetCollisionData().aabb, objs[i].GetPosition(), objs[j].GetPosition()))
				{
					if (OOBBCollision(objs[i].GetCollisionData().oobb, objs[j].GetCollisionData().oobb, objs[i].GetPosition(), objs[j].GetPosition()))
					{
						m_CollisionIndices.oobbCollision.push_back(i);
						m_CollisionIndices.oobbCollision.push_back(j);
					}
					else
					{
						m_CollisionIndices.aabbCollision.push_back(i);
						m_CollisionIndices.aabbCollision.push_back(j);
					}
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
				if (AABBCollision(objs[i].GetCollisionData().aabb, objs[j].GetCollisionData().aabb, objs[i].GetPosition(), objs[j].GetPosition()))
				{
					if (OOBBCollision(objs[i].GetCollisionData().oobb, objs[j].GetCollisionData().oobb, objs[i].GetPosition(), objs[j].GetPosition()))
					{
						m_CollisionIndices.oobbCollision.push_back(i);
						m_CollisionIndices.oobbCollision.push_back(j);
					}
					else
					{
						m_CollisionIndices.aabbCollision.push_back(i);
						m_CollisionIndices.aabbCollision.push_back(j);
					}
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
			if (AABBCollision(objs[i].GetCollisionData().aabb, objs[m_freeObject].GetCollisionData().aabb, objs[i].GetPosition(), objs[m_freeObject].GetPosition()))
			{
				if (OOBBCollision(objs[i].GetCollisionData().oobb, objs[m_freeObject].GetCollisionData().oobb, objs[i].GetPosition(), objs[m_freeObject].GetPosition()))
				{
					m_CollisionIndices.oobbCollision.push_back(i);
					m_CollisionIndices.oobbCollision.push_back(m_freeObject);
				}
				else
				{
					m_CollisionIndices.aabbCollision.push_back(i);
					m_CollisionIndices.aabbCollision.push_back(m_freeObject);
				}
			}
			else
			{
				m_CollisionIndices.circleCollision.push_back(i);
				m_CollisionIndices.circleCollision.push_back(m_freeObject);
			}
		}
	}
}
