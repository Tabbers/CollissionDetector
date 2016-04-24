#pragma once
#include "SFML\Graphics.hpp"
#include "Object2D.h"

class Display
{
public:
	Display(sf::RenderWindow* window);
	~Display();
	
	void Init(unsigned int, Object2D*);
	void UpdateDynamicObjects(Object2D*);
	void Render();

private:
	unsigned int m_NumberOfTriangles_static=0;

	unsigned int m_NumberOfTriangles_dynamic = 0;

	sf::RenderWindow* window;
	sf::ConvexShape* m_triangles;
	sf::CircleShape* m_boundingCircles;
	sf::RectangleShape* m_aabs;
	sf::RectangleShape* m_oobbs;
};

