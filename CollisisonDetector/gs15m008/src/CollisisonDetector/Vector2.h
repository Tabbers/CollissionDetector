#pragma once

#ifndef SFML_VECTOR2_HPP
#define SFML_VECTOR2_HPP

namespace sf
{
	template <typename T>
	class Vector2
	{
	public:
		Vector2();
		Vector2(T X, T Y);
		template <typename U>
		explicit Vector2(const Vector2<U>& vector);
		// Member data
		T x;
		T y;
	};
	template <typename T>
	Vector2<T> operator -(const Vector2<T>& right);

	template <typename T>
	Vector2<T>& operator +=(Vector2<T>& left, const Vector2<T>& right);

	template <typename T>
	Vector2<T>& operator -=(Vector2<T>& left, const Vector2<T>& right);

	template <typename T>
	Vector2<T> operator +(const Vector2<T>& left, const Vector2<T>& right);

	template <typename T>
	Vector2<T> operator -(const Vector2<T>& left, const Vector2<T>& right);

	template <typename T>
	Vector2<T> operator *(const Vector2<T>& left, T right);

	template <typename T>
	Vector2<T> operator *(T left, const Vector2<T>& right);

	template <typename T>
	Vector2<T>& operator *=(Vector2<T>& left, T right);

	template <typename T>
	Vector2<T> operator /(const Vector2<T>& left, T right);

	template <typename T>
	Vector2<T>& operator /=(Vector2<T>& left, T right);

	template <typename T>
	bool operator ==(const Vector2<T>& left, const Vector2<T>& right);

	template <typename T>
	bool operator !=(const Vector2<T>& left, const Vector2<T>& right);

#include <SFML/System/Vector2.inl>
	// Define the most common types
	typedef Vector2<int>          Vector2i;
	typedef Vector2<unsigned int> Vector2u;
	typedef Vector2<float>        Vector2f;
} // namespace sf
#endif // SFML_VECTOR2_HPP

class Vector2
{
public:
	 template <typename T>
	 inline Vector2(T src)
	 {
		 this->x = src.x;
		 this->y = src.y;
	 };
	 Vector2(float,float);
	 Vector2();
	 ~Vector2();
	 void operator=(const Vector2 &rhs);
	 void operator+=(const Vector2 &rhs);
	 Vector2 operator+(const Vector2 &rhs) const;
	 Vector2 operator-(const Vector2 &rhs) const;
	 Vector2 operator*(const float rhs)   const;
	 Vector2 operator*(const Vector2 &rhs) const;
	 Vector2 operator/(const float rhs)   const;
	 bool operator==(const Vector2 &rhs)   const;
	 bool operator>(const Vector2 &rhs)    const;
	 bool operator<(const Vector2 &rhs)    const;
	 Vector2 invert()					   const;
	 Vector2 rotate90()					   const;
	 Vector2& rotateAroundPoint(Vector2 pivot, float angle);
	 Vector2& rotate(float); 
	 Vector2 Normalize()				   const;
	 float Length()						   const;
	 float SqrLength()					   const;
	 float GetAngleRad()				   const;
	 float GetAngleDeg()				   const;
	 float dot(const Vector2& rhs)		   const;
	 sf::Vector2f toVector2f()			   const;
	 sf::Vector2i toVector2i()			   const;
	 sf::Vector2u toVector2u()			   const;
public:
	float x=0;
	float y = 0;
	const float PI = 3.1415927410125732421875f;
	const float EPSILON = 0.00001;
};

