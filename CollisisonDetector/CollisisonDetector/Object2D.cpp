#include "Object2D.h"

void Object2D::PatchCollisionCenter()
{
	m_colData.c.center = m_position;
}
