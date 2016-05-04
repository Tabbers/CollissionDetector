#pragma once
#include "Triangle.h"
#include "CollisionData.h"

class Object2D
{

public:
	inline Object2D()  {};
	inline ~Object2D() {};
	
	inline void SetObject2D(Triangle triangle, CollisionData coldata)
	{
		this->m_triangle = triangle;
		this->m_colData   = coldata;
	}

	inline void SetPosition(Vector2 pos) { this->m_position = pos; }
	inline void SetSpeed(Vector2 speed)  { this->m_speed = speed; }

	inline Vector2 GetPosition() { return m_position; };
	inline Vector2 GetSpeed()   { return m_speed; };

	inline Triangle GetTriangle() { return m_triangle; }
	inline CollisionData GetCollisionData() { return m_colData; }

	void PatchCollisionCenter();
private:
	Vector2 m_position;
	Vector2 m_speed;

	Triangle		m_triangle;
	CollisionData	m_colData;
};