#include "display.h"
#include "Triangle.h"
#include "CollisionData.h"

Display::Display(sf::RenderWindow* window):window(window)
{
}


Display::~Display()
{
}

void Display::Init(unsigned int NumberOfTriangles, Object2D* objs)
{

	m_triangles		  = new sf::ConvexShape[NumberOfTriangles];
	m_boundingCircles = new sf::CircleShape[NumberOfTriangles];
	m_aabs			  = new sf::RectangleShape[NumberOfTriangles];

	m_NumberOfTriangles_static  = NumberOfTriangles - 11; 
	m_NumberOfTriangles_dynamic = NumberOfTriangles - 100;
	unsigned int UniformBounds = m_NumberOfTriangles_static / 10;

	for (unsigned int i = 0; i < m_NumberOfTriangles_static+m_NumberOfTriangles_dynamic; ++i)
	{
		m_triangles[i].setPointCount(3);
		m_triangles[i].setOutlineColor(sf::Color(0, 0, 255));
		m_triangles[i].setFillColor(sf::Color::Transparent);
		m_triangles[i].setOutlineThickness(1);

		m_triangles[i].setPoint(0, objs[i].GetTriangle().points[0].toVector2f());
		m_triangles[i].setPoint(1, objs[i].GetTriangle().points[1].toVector2f());
		m_triangles[i].setPoint(2, objs[i].GetTriangle().points[2].toVector2f());

		m_boundingCircles[i].setRadius(objs[i].GetCollisionData().c.radius);
		m_boundingCircles[i].setOutlineColor(sf::Color(255, 0, 0));
		m_boundingCircles[i].setFillColor(sf::Color::Transparent);
		m_boundingCircles[i].setOutlineThickness(1);

		m_aabs[i].setSize((objs[i].GetCollisionData().abb.Halfbounds * 2).toVector2f());
		m_aabs[i].setOutlineColor(sf::Color(255, 0, 0));
		m_aabs[i].setFillColor(sf::Color::Transparent);
		m_aabs[i].setOutlineThickness(1);


	}
	unsigned int stepx  = window->getSize().x / 10;
	unsigned int stepy  = window->getSize().y / 10;

	Vector2 pos;
	int index;
	for (unsigned int y = 0; y < UniformBounds; ++y)
	{
		for (unsigned int x = 0; x < UniformBounds; ++x)
		{
			index = x + UniformBounds * y;

			pos.x = x*stepx + (stepx / 2) + objs[index].GetTriangle().center.x;
			pos.y = y*stepy + (stepy / 2) + objs[index].GetTriangle().center.y;
			
			m_triangles[index].setPosition(pos.toVector2f());
			
			m_boundingCircles[index].setPosition(pos.toVector2f());
			m_boundingCircles[index].setOrigin(objs[index].GetCollisionData().c.radius - objs[index].GetTriangle().center.x, objs[index].GetCollisionData().c.radius - objs[index].GetTriangle().center.y);
		
			m_aabs[index].setPosition(pos.toVector2f());
			m_aabs[index].setOrigin(objs[index].GetCollisionData().abb.Halfbounds.x - objs[index].GetTriangle().center.x, objs[index].GetCollisionData().abb.Halfbounds.y - objs[index].GetTriangle().center.y);
		}
	}
	for (unsigned int i = m_NumberOfTriangles_static; i < m_NumberOfTriangles_static + m_NumberOfTriangles_dynamic; ++i)
	{
		pos = objs[i].GetPosition();
		
		m_triangles[i].setPosition(pos.toVector2f());
		m_triangles[i].setOutlineColor(sf::Color(0,255,0));

		m_boundingCircles[i].setPosition(pos.toVector2f());
		m_boundingCircles[i].setOrigin(objs[i].GetCollisionData().c.radius - objs[i].GetTriangle().center.x, objs[i].GetCollisionData().c.radius - objs[i].GetTriangle().center.y);

		m_aabs[i].setPosition(pos.toVector2f());
		m_aabs[i].setOrigin(objs[i].GetCollisionData().abb.Halfbounds.x - objs[i].GetTriangle().center.x, objs[i].GetCollisionData().abb.Halfbounds.y - objs[i].GetTriangle().center.y);

	}
	m_triangles[110].setOutlineColor(sf::Color(255, 255, 0));
}
void Display::UpdateDynamicObjects(Object2D* objs)
{
	Vector2 pos;
	for (unsigned int i = m_NumberOfTriangles_static; i < m_NumberOfTriangles_static + m_NumberOfTriangles_dynamic; ++i)
	{
		pos = objs[i].GetPosition();
		m_triangles[i].setPosition(pos.toVector2f());
		m_boundingCircles[i].setPosition(pos.toVector2f());
		m_aabs[i].setPosition(pos.toVector2f());
	}
}

void Display::Render()
{
	for (unsigned int i = 0; i < m_NumberOfTriangles_static+m_NumberOfTriangles_dynamic; ++i)
	{
		window->draw(m_triangles[i]);
		window->draw(m_boundingCircles[i]);
		window->draw(m_aabs[i]);
	}
}
 
