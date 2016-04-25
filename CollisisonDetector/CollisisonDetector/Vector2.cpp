#include "vector2.h"
#include <math.h>

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2::Vector2()
{
	x = 0;
	y = 0;
}


Vector2::~Vector2()
{
}

void Vector2::operator=(const Vector2 & rhs)
{
	x = rhs.x;
	y = rhs.y;
}

void Vector2::operator+=(const Vector2 & rhs)
{
	x +=  rhs.x;
	y +=  rhs.y;
}

Vector2 Vector2::operator+(const Vector2 &rhs)
{
	Vector2 temp;
	temp.x = x + rhs.x;
	temp.y = y + rhs.y;
	return temp;
}
Vector2 Vector2::operator-(const Vector2 &rhs)
{
	Vector2 temp;
	temp.x = x - rhs.x;
	temp.y = y - rhs.y;
	return temp;
}
Vector2 Vector2::operator*(const float &rhs)
{
	Vector2 temp;
	temp.x = x * rhs;
	temp.y = y * rhs;
	return temp;
}
Vector2 Vector2::operator*(const Vector2 &rhs)
{
	Vector2 temp;
	temp.x *= rhs.x;
	temp.y *= rhs.y;
	return temp;
}

Vector2 Vector2::operator/(const float & rhs)
{
	Vector2 temp;
	temp.x = x / rhs;
	temp.y = y / rhs;
	return temp;
	return Vector2();
}

bool Vector2::operator==(const Vector2 & rhs)
{
	return rhs.x==this->x && rhs.y==this->y;
}

bool Vector2::operator>(const Vector2 & rhs)
{
	return (rhs.x > this->x) && (rhs.y > this->y);
}

bool Vector2::operator<(const Vector2 & rhs)
{
		return (rhs.x < this->x) && (rhs.y < this->y);
}

Vector2 Vector2::invert()
{
	Vector2 temp;
	temp.x = -x;
	temp.y = -y;
	return temp;
}

Vector2 Vector2::rotate(float angle)
{
	Vector2 temp;

	float theta = angle*PI/180;
	float l = this->GetAngleRad();
	float length = this->Length();

	temp.x = cos(theta + l)*length;
	temp.y = sin(theta + l)*length;

	*this = temp;
	return temp;
}

Vector2 Vector2::Normalize()
{
	Vector2 temp;
	float length = this->Length();
	if (length < EPSILON && length > -EPSILON) length = 1;
	temp.x = x / length;
	temp.y = y / length;
	return temp;
}

float Vector2::Length()
{
	float result = sqrt(pow(this->x, 2) + pow(this->y, 2));
	return result;
}

float Vector2::SqrLength()
{
	float result = pow(this->x, 2) + pow(this->y, 2);
	return result;
}

float Vector2::GetAngleRad()
{
	float temp=atan2f(y,x);
	return temp;
}

float Vector2::GetAngleDeg()
{
	return (GetAngleRad() * 180) / PI;
}
float Vector2::dot(const Vector2& rhs)
{
	return this->x*rhs.y+this->y*rhs.x;
}

sf::Vector2f Vector2::toVector2f()
{
	sf::Vector2f vec2f;
	vec2f.x = x;
	vec2f.y = y;
	return vec2f;
}

sf::Vector2i Vector2::toVector2i()
{
	sf::Vector2i vec2i;
	vec2i.x = static_cast<int>(x);
	vec2i.y = static_cast<int>(y);
	return vec2i;
}

sf::Vector2u Vector2::toVector2u()
{
	sf::Vector2u vec2u;
	vec2u.x = static_cast<unsigned int>(x);
	vec2u.y = static_cast<unsigned int>(y);
	return vec2u;
}

Vector2 Vector2::rotate90()
{
	if (x > 0)		return Vector2(0 , 1);
	else if (x < 0) return Vector2(0 , -1);
	else if (y > 0) return Vector2(-1 , 0);
	else if (y < 0) return Vector2(1 , 0);
	return Vector2();
}

Vector2 Vector2::rotateAroundPoint(Vector2 pivot, float angle)
{
	float theta = angle * PI / 180;
	
	Vector2 tempVect(x - pivot.x, y - pivot.y);
	tempVect.rotate(angle);
	tempVect += pivot;

	*this = tempVect;
	return *this;
}
