#include "display.h"
#include "Triangle.h"
#include "CollisionData.h"

Display::Display(sf::RenderWindow* window):window(window)
{
	font.loadFromFile("../font/font.otf");
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
	m_aabbs			  = new sf::ConvexShape[NumberOfTriangles];
	m_oobbs			  = new sf::ConvexShape[NumberOfTriangles];

	m_NumberOfTriangles_static  = NumberOfTriangles - 11; 
	m_NumberOfTriangles_dynamic = NumberOfTriangles - 100;


	for (unsigned int i = 0; i < m_NumberOfTriangles_static+m_NumberOfTriangles_dynamic; ++i)
	{
		m_triangles[i].setPointCount(3);
		m_triangles[i].setOutlineColor(sf::Color(0, 0, 255));
		m_triangles[i].setFillColor(sf::Color::Transparent);
		m_triangles[i].setOutlineThickness(-1);

		m_triangles[i].setPoint(0, objs[i].GetTriangle().points[0].toVector2f());
		m_triangles[i].setPoint(1, objs[i].GetTriangle().points[1].toVector2f());
		m_triangles[i].setPoint(2, objs[i].GetTriangle().points[2].toVector2f());

		m_boundingCircles[i].setRadius(objs[i].GetCollisionData().c.radius);
		m_boundingCircles[i].setOutlineColor(sf::Color(255, 0, 0));
		m_boundingCircles[i].setFillColor(sf::Color::Transparent);
		m_boundingCircles[i].setOutlineThickness(-1);

		Vector2 ul = objs[i].GetCollisionData().aabb.ul;
		Vector2 ur = {objs[i].GetCollisionData().aabb.dr.x,objs[i].GetCollisionData().aabb.ul.y };
		Vector2 dr = objs[i].GetCollisionData().aabb.dr;
		Vector2 dl = {objs[i].GetCollisionData().aabb.ul.x,objs[i].GetCollisionData().aabb.dr.y };;

		m_aabbs[i].setPointCount(4);
		  
		m_aabbs[i].setPoint(0, ul.toVector2f());
		m_aabbs[i].setPoint(1, ur.toVector2f());
		m_aabbs[i].setPoint(2, dr.toVector2f());
		m_aabbs[i].setPoint(3, dl.toVector2f());

		m_aabbs[i].setOutlineColor(sf::Color(255, 0, 0));
		m_aabbs[i].setFillColor(sf::Color::Transparent);
		m_aabbs[i].setOutlineThickness(-1);

		m_oobbs[i].setPointCount(4);

		m_oobbs[i].setPoint(0, objs[i].GetCollisionData().oobb.ul.toVector2f());
		m_oobbs[i].setPoint(1, objs[i].GetCollisionData().oobb.ur.toVector2f());
		m_oobbs[i].setPoint(2, objs[i].GetCollisionData().oobb.dr.toVector2f());
		m_oobbs[i].setPoint(3, objs[i].GetCollisionData().oobb.dl.toVector2f());

		m_oobbs[i].setOutlineColor(sf::Color(255, 0, 0));
		m_oobbs[i].setFillColor(sf::Color::Transparent);
		m_oobbs[i].setOutlineThickness(1);
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
		m_boundingCircles[i].setOrigin(objs[i].GetCollisionData().c.radius ,objs[i].GetCollisionData().c.radius);

		m_aabbs[i].setPosition(pos.toVector2f());

		m_oobbs[i].setPosition(pos.toVector2f());

		m_oobbs[i].setOutlineColor(sf::Color(255, 0, 0));
		m_oobbs[i].setFillColor(sf::Color::Transparent);
		m_oobbs[i].setOutlineThickness(-1);
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
		m_aabbs[i].setPosition(pos.toVector2f());
		m_oobbs[i].setPosition(pos.toVector2f());
	}
	for (unsigned int i = 0; i < m_NumberOfTriangles_dynamic + m_NumberOfTriangles_static; ++i)
	{
		m_triangles[i].setFillColor(sf::Color::Transparent);
	}
}

void Display::Render(CollisionDetector::CollidingObjects collidingObjects)
{
	for (unsigned int i = 0; i < collidingObjects.MikowskiCollision.size(); ++i)
	{
		m_triangles[collidingObjects.MikowskiCollision[i]].setFillColor(sf::Color::Cyan);
	}
	for (unsigned int i = 0; i < m_NumberOfTriangles_static + m_NumberOfTriangles_dynamic; ++i)
	{
		window->draw(m_triangles[i]);
	}
	for (unsigned int i = 0; i < collidingObjects.circleCollision.size(); ++i)
	{
		window->draw(m_boundingCircles[collidingObjects.circleCollision[i]]);
	}
	for (unsigned int i = 0; i < collidingObjects.aabbCollision.size(); ++i)
	{
		window->draw(m_aabbs[collidingObjects.aabbCollision[i]]);
	}
	for (unsigned int i = 0; i < collidingObjects.oobbCollision.size(); ++i)
	{
		window->draw(m_oobbs[collidingObjects.oobbCollision[i]]);
	}

	window->draw(fps);
}
 
