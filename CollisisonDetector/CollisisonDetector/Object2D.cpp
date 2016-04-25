#include "Object2D.h"

void Object2D::PathCollisionCenter()
{
	m_colData.c.center = m_position;
	m_colData.aabb.center = m_position;
}
