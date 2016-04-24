#pragma once
#include "Vector2.h"

class Object2D;

class Simulation
{
public:
	Simulation();
	~Simulation();
	
	//100 static | 10 dynamic | 1 mouse
	const int NumberOfTriangles = 111;

	//GETER

	inline Object2D* get2DObjects() { return m_objs; };

	void Init(Vector2);
	void Update(float, Vector2);

private:
	Object2D* m_objs;
	Vector2 m_SimulationBounds;
};

