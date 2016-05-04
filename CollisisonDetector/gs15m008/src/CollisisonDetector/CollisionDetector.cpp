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

bool CollisionDetector::AABBCollision(CollisionData::AABB &left , CollisionData::AABB &right, Vector2 &posl, Vector2& posr)
{
	Vector2 minleft  = posl + left.ul;
	Vector2 maxleft  = posl + left.dr;
	Vector2 minRight = posr + right.ul;
	Vector2 maxRight = posr + right.dr;

	return maxleft > minRight && maxRight > minleft;
}

bool CollisionDetector::OOBBCollision(CollisionData::OOBB &left, CollisionData::OOBB &right, Vector2 &posl, Vector2 &posr)
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

	return (OOBCollisionSingleObject(leftHelper,rightHelper) && OOBCollisionSingleObject(rightHelper, leftHelper));
}

bool CollisionDetector::OOBCollisionSingleObject(CollisionData::OOBB &left, CollisionData::OOBB &right)
{
	Vector2 axisX = (left.dr - left.dl).Normalize();
	Vector2 axisY = (left.ul - left.dl).Normalize();

	Vector2 extents = { (left.dr - left.dl).Length(),(left.ul - left.dl).Length() };

	Vector2 rightul = right.ul - left.dl;
	Vector2 rightur = right.ur - left.dl;
	Vector2 rightdr = right.dr - left.dl;
	Vector2 rightdl = right.dl - left.dl;

	float projectedLengthUl = rightul.dot(axisX);
	float projectedLengthUr = rightur.dot(axisX);
	float projectedLengthDr = rightdr.dot(axisX);
	float projectedLengthDl = rightdl.dot(axisX);

	if ((projectedLengthUl > extents.x || projectedLengthUl < 0.0f) &&
		(projectedLengthUr > extents.x || projectedLengthUr < 0.0f) &&
		(projectedLengthDr > extents.x || projectedLengthDr < 0.0f) &&
		(projectedLengthDl > extents.x || projectedLengthDl < 0.0f))
		return false;

	projectedLengthUl = rightul.dot(axisY);
	projectedLengthUr = rightur.dot(axisY);
	projectedLengthDr = rightdr.dot(axisY);
	projectedLengthDl = rightdl.dot(axisY);

	if ((projectedLengthUl > extents.y || projectedLengthUl < 0.0f) &&
		(projectedLengthUr > extents.y || projectedLengthUr < 0.0f) &&
		(projectedLengthDr > extents.y || projectedLengthDr < 0.0f) &&
		(projectedLengthDl > extents.y || projectedLengthDl < 0.0f))
		return false;

	return true;
}

bool CollisionDetector::MikowskiCollisison(Triangle &left, Triangle &right, Vector2 &posl, Vector2 &posr)
{
	std::vector<Vector2> points;
	points.reserve(9);

	Triangle leftWorldSpace;
	Triangle rightWorldSpace;

	for (unsigned int i = 0; i < 3; ++i)
	{
		leftWorldSpace.points[i]  = left.points[i]  + posl;
		rightWorldSpace.points[i] = right.points[i] + posr;
	}
	//iterate throught the left Triangle
	for (unsigned int l = 0; l < 3; ++l)
	{
		// iterate through the right triangle
		for (unsigned int r = 0; r < 3; ++r)
		{
			Vector2 pointToAdd = leftWorldSpace.points[l] - rightWorldSpace.points[r];
			bool dublicatePoints = false;

			for (unsigned int i = 0; i < points.size(); ++i)
			{
				if (pointToAdd == points[i])
				{
					dublicatePoints == true;
					break;
				}
			}
			if(!dublicatePoints)
				points.push_back(pointToAdd);
		}
	}

	points = JarvisMarch(points);
	Vector2 origin;
	for (unsigned int i = 0; i < points.size() - 1; ++i)
	{
		if (Rightturn(points[i], points[i + 1], origin) == 1)
			return false;
	}

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
						if (MikowskiCollisison(objs[i].GetTriangle(), objs[j].GetTriangle(), objs[i].GetPosition(), objs[j].GetPosition()))
						{
							m_CollisionIndices.MikowskiCollision.push_back(i);
							m_CollisionIndices.MikowskiCollision.push_back(j);
						}
						else
						{
							m_CollisionIndices.oobbCollision.push_back(i);
							m_CollisionIndices.oobbCollision.push_back(j);
						}
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
					if (MikowskiCollisison(objs[i].GetTriangle(), objs[j].GetTriangle(), objs[i].GetPosition(), objs[j].GetPosition()))
					{
						m_CollisionIndices.MikowskiCollision.push_back(i);
						m_CollisionIndices.MikowskiCollision.push_back(j);
					}
					else
					{
						m_CollisionIndices.oobbCollision.push_back(i);
						m_CollisionIndices.oobbCollision.push_back(j);
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
					if(MikowskiCollisison(objs[i].GetTriangle(), objs[m_freeObject].GetTriangle(), objs[i].GetPosition(), objs[m_freeObject].GetPosition()))
					{
						m_CollisionIndices.MikowskiCollision.push_back(i);
						m_CollisionIndices.MikowskiCollision.push_back(m_freeObject);
					}
					else
					{
						m_CollisionIndices.oobbCollision.push_back(i);
						m_CollisionIndices.oobbCollision.push_back(m_freeObject);
					}
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

std::vector<Vector2> CollisionDetector::JarvisMarch(std::vector<Vector2> points)
{
	std::vector<Vector2> result;
	// ************* find left most point ********************
	int  p = 0;
	int  l;
	for (int i = 1; i<points.size(); ++i)
	{
		if (points[i].x < points[p].x)
		{
			p = i;
		}
		else if (points[i].x == points[p].x && points[i].y < points[p].y)
		{
			p = i;
		}
	}
	// start point = left most point
	l = p;
	// calculate next point
	int  q = (p + 1) % points.size();

	// if less than 3 elements -> nothing to compute
	if (points.size()<3)
	{
		for (int i = 0; i<points.size(); i++)
		{
			result.push_back(points[i]);
		}
	}
	else
	{
		do  // as long as point on hull is not the left most point
		{
			// add left most point and the points to follow
			result.push_back(points[p]);
			for (int r = 0; r<points.size(); r++)
			{
				// Counter-clockwise -> if turn right -> set new point
				if (Rightturn(points[p], points[q], points[r]) == 1)
				{
					// if turn right then set current point as next point on the hull -> rightturn is called with updated value
					q = r;
				}
			}
			// set final q to next point on hull
			p = q;
			// go to next point in array after hullpoint
			q = (p + 1) % points.size();
		} while (p != l);
		// add left most point twice for drawing
		result.push_back(points[p]);
	}
	return result;
}

int  CollisionDetector::Rightturn(Vector2 p, Vector2 q, Vector2 r)
{
	// cross product to determine polygon orientation
	double x1 = (q.x - p.x) * (r.y - p.y);
	double x2 = (r.x - p.x) * (q.y - p.y);
	double val = x1 - x2;

	if (val == 0)
		return 0;
	if (val>0)   // CCW orientation
		return 1;
	else
		return -1;
}