#include "Simulation.h"
#include "Triangle.h"
#include "CollisionData.h"
#include "Object2D.h"
#include "Randomizer.h"

Simulation::Simulation()
{
}


Simulation::~Simulation()
{
}

void Simulation::Init(Vector2 Simulationbounds)
{
	m_SimulationBounds = Simulationbounds;
	m_objs = new Object2D[NumberOfTriangles];
	unsigned int UniformBounds = (NumberOfTriangles-11) / 10;

	for (unsigned int i = 0; i < NumberOfTriangles; ++i)
	{
		Triangle tri;
		CollisionData col;
		tri.Generate(40, 40);
		col.GenerateDataFormTriangle(tri);
		m_objs[i].SetObject2D(tri, col);
	}
	Vector2 pos;
	Vector2 speed;
	Vector2 paddingXY((m_SimulationBounds / 10).x, (m_SimulationBounds / 10).y);
	
	unsigned int stepx = Simulationbounds.x / 10;
	unsigned int stepy = Simulationbounds.y / 10;
	int index;

	for (unsigned int y = 0; y < UniformBounds; ++y)
	{
		for (unsigned int x = 0; x < UniformBounds; ++x)
		{
			index = x + UniformBounds * y;

			pos.x = x*stepx + (stepx / 2) + m_objs[index].GetTriangle().center.x;
			pos.y = y*stepy + (stepy / 2) + m_objs[index].GetTriangle().center.y;
			m_objs[index].SetPosition(pos);
		}
	}
	for (unsigned int i = 100; i < (NumberOfTriangles-1); ++i)
	{
		pos.x = Randomizer::GetRandom(0.f + paddingXY.x, m_SimulationBounds.x - paddingXY.x);
		pos.y = Randomizer::GetRandom(0.f + paddingXY.y, m_SimulationBounds.y - paddingXY.y);

		speed.x = Randomizer::GetRandom(-50, 50);
		speed.y = Randomizer::GetRandom(-50, 50);

		m_objs[i].SetPosition(pos);
		m_objs[i].SetSpeed(speed);
	}
	//CollisionDataPatchUp
	for (unsigned int i = 0; i < NumberOfTriangles; ++i)
	{
		m_objs[i].PatchCollisionCenter();
	}

	m_coldetect = new CollisionDetector(100, 10, 1);
}

void Simulation::Update(float deltatime, Vector2 mousePos)
{
	Vector2 pos;
	for (unsigned int i = 100; i < (NumberOfTriangles - 1); ++i)
	{
		pos = m_objs[i].GetPosition();
		pos += m_objs[i].GetSpeed() * deltatime;

		//Wraparound
		//Check x bounds
		if (pos.x > m_SimulationBounds.x)
			pos.x = 0.5;
		if (pos.x < 0)
			pos.x = m_SimulationBounds.x - 0.5;
		
		//Check y bounds
		if (pos.y > m_SimulationBounds.y)
			pos.y = 0.5;
		if (pos.y < 0)
			pos.y = m_SimulationBounds.y - 0.5;

		m_objs[i].SetPosition(pos);
		m_objs[i].PatchCollisionCenter();
	}
	pos = mousePos;
	pos = pos - m_objs[110].GetTriangle().center;
	m_objs[110].SetPosition(pos);
	m_objs[110].PatchCollisionCenter();

	m_coldetect->CheckForCollisions(m_objs);
}
