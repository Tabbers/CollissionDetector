#pragma once
#include "Object2D.h"
#include "CollisionData.h"
#include "Triangle.h"
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
	//left|right
	bool CircleCollision(CollisionData::Circle&, CollisionData::Circle&);
	
	//left|right|posl|posr
	bool AABBCollision(CollisionData::AABB&, CollisionData::AABB&, Vector2&,Vector2&);

	//left|right|posl|posr
	bool OOBBCollision(CollisionData::OOBB&, CollisionData::OOBB&, Vector2&, Vector2&);

	//left|right
	bool OOBCollisionSingleObject(CollisionData::OOBB&, CollisionData::OOBB&);

	//left|right|posl|posr
	bool MikowskiCollisison(Triangle&, Triangle&, Vector2&, Vector2&);


	void CheckDynamicVsStatic(Object2D *);
	void CheckDynamicVsDynamic(Object2D *);
	void ChekcStaticDynamicVsFree(Object2D *);

	std::vector<Vector2> JarvisMarch(std::vector<Vector2>);
	int Rightturn(Vector2 p, Vector2 q, Vector2 r);

	CollidingObjects m_CollisionIndices;
	unsigned int m_staticObjects	= 0;
	unsigned int m_dynamicObjects	= 0;
	unsigned int m_freeObject	= 0;

};

