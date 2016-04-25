#pragma once
#include "Object2D.h"
#include "CollisionData.h"
#include <vector>

class CollisionDetector
{
public:
	struct CollidingObjects
	{
		std::vector<int> circleCollision;
		std::vector<int> aabbCollision;
		std::vector<int> oobbCollision;
		std::vector<int> MikowskiCollision;
	};
public:
	CollisionDetector(unsigned int, unsigned int, unsigned int);
	CollisionDetector();
	~CollisionDetector();
	void CheckForCollisions(Object2D*);
	inline CollidingObjects GetCollidingObjects() { return m_CollisionIndices; };
private:

	bool CircleCollision(CollisionData::Circle&, CollisionData::Circle&);
	
	//left|right|posl|posr
	bool AABBCollision(CollisionData::AABB&, CollisionData::AABB&, Vector2,Vector2);

	//left|right|posl|posr
	bool OOBBCollision(CollisionData::OOBB&, CollisionData::OOBB&, Vector2, Vector2);

	bool OOBCollisionSingleObject(CollisionData::OOBB&, CollisionData::OOBB&);

	void CheckDynamicVsStatic(Object2D *);
	void CheckDynamicVsDynamic(Object2D *);
	void ChekcStaticDynamicVsFree(Object2D *);

	CollidingObjects m_CollisionIndices;
	unsigned int m_staticObjects	= 0;
	unsigned int m_dynamicObjects	= 0;
	unsigned int m_freeObject	= 0;

};

