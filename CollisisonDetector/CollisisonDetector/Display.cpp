#include "display.h"
#include "Triangle.h"
#include "CollisionData.h"

Display::Display(sf::RenderWindow* window):window(window)
{
	font.loadFromFile("font/font.ttf");
	fps.setFont(font);

	fps.setCharacterSize(24);
	fps.setPosition(20, 48);
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

		m_aabs[i].setSize((objs[i].GetCollisionData().aabb.Halfbounds * 2).toVector2f());
		m_aabs[i].setOutlineColor(sf::Color(255, 0, 0));
		m_aabs[i].setFillColor(sf::Color::Transparent);
		m_aabs[i].setOutlineThickness(1);
	}

	Vector2 pos;
	int index;
	for (unsigned int i = 0; i < m_NumberOfTriangles_static + m_NumberOfTriangles_dynamic; ++i)
	{
		pos = objs[i].GetPosition();
		
		m_triangles[i].setPosition(pos.toVector2f());
		if(i>=100)
			m_triangles[i].setOutlineColor(sf::Color(0,255,0));
		else 
			m_triangles[i].setOutlineColor(sf::Color(0, 0, 255));
		m_boundingCircles[i].setPosition(pos.toVector2f());
		m_boundingCircles[i].setOrigin(objs[i].GetCollisionData().c.radius - objs[i].GetTriangle().center.x, objs[i].GetCollisionData().c.radius - objs[i].GetTriangle().center.y);

		m_aabs[i].setPosition(pos.toVector2f());
		m_aabs[i].setOrigin(objs[i].GetCollisionData().aabb.Halfbounds.x - objs[i].GetTriangle().center.x, objs[i].GetCollisionData().aabb.Halfbounds.y - objs[i].GetTriangle().center.y);

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

void Display::Render(CollisionDetector::CollidingObjects collidingObjects)
{
	for (unsigned int i = 0; i < collidingObjects.circleCollision.size(); ++i)
	{
		window->draw(m_boundingCircles[collidingObjects.circleCollision[i]]);
	}
	for (unsigned int i = 0; i < collidingObjects.aabbCollision.size(); ++i)
	{
		window->draw(m_aabs[collidingObjects.aabbCollision[i]]);
	}
	for (unsigned int i = 0; i < m_NumberOfTriangles_static+m_NumberOfTriangles_dynamic; ++i)
	{
		window->draw(m_triangles[i]);
	}
	window->draw(fps);
}
 
