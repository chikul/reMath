//////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:        reVec2d.cpp
// Project:     reMath
// Description: Implementation of Vec2d class
// Copyright:   Copyright ? 2004++ REGLabs
// Author:      Pavel Chikul
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "reMath/reVec2d.h"
#include <cstring>
#include <cmath>

re::Vec2d::Vec2d()
{
	memset(d, 0, sizeof(d));
}


re::Vec2d::Vec2d(const Vec2d& vector)
{
	set(vector);
}


re::Vec2d::Vec2d(const Vec2d* vector)
{
	set(vector->d);
}


re::Vec2d::Vec2d(float value)
{
	set(value);
}


re::Vec2d::Vec2d(float xValue, float yValue)
{
	set(xValue, yValue);
}


re::Vec2d::Vec2d(const float* vector)
{
	set(vector);
}


void re::Vec2d::set(const Vec2d& vector)
{
	x = vector.x;
	y = vector.y;
}


void re::Vec2d::set(float value)
{
	x = value;
	y = value;
}


void re::Vec2d::set(float xValue, float yValue)
{
	x = xValue;
	y = yValue;
}


void re::Vec2d::set(const float* vector)
{
	memcpy(&d, vector, sizeof(d));
}


float re::Vec2d::length() const
{
	return sqrt(x * x + y * y);
}


float re::Vec2d::distanceTo(const Vec2d & vector) const
{
	const float dx = x - vector.x;
	const float dy = y - vector.y;
	return sqrt(dx * dx + dy * dy);
}


bool re::Vec2d::isParallel(const Vec2d& vector) const
{
	return ((x / vector.x) == (y / vector.y));
}


void re::Vec2d::normalize()
{
	const float d = length();

	if (d)
	{
		x /= d;
		y /= d;
	}
	else
	{
		set(0, 0);
	}
}


void re::Vec2d::negate()
{
	x = -x;
	y = -y;
}


float re::Vec2d::cross(const Vec2d& vector) const
{
	return (x * vector.y - y * vector.x);
}


float re::Vec2d::dot(const Vec2d& vector) const
{
	return (x * vector.x + y * vector.y);
}


bool re::Vec2d::operator == (const Vec2d& vector) const
{
	return (x == vector.x && y == vector.y);
}


bool re::Vec2d::operator != (const Vec2d& vector) const
{
	return (x != vector.x || y != vector.y);
}


re::Vec2d& re::Vec2d::operator = (const Vec2d& vector)
{
	if (&vector != this)
		memcpy(d, vector.d, sizeof(d));

	return *this;
}


re::Vec2d re::Vec2d::operator - () const
{
	Vec2d result(this);
	result.negate();
	return result;
}


re::Vec2d re::Vec2d::operator + (const Vec2d& vector) const
{
	return Vec2d(x + vector.x, y + vector.y);
}


re::Vec2d re::Vec2d::operator - (const Vec2d& vector) const
{
	return Vec2d(x - vector.x, y - vector.y);
}


re::Vec2d re::operator * (float value, const re::Vec2d& vector)
{
	return re::Vec2d(vector.x * value, vector.y * value);
}


re::Vec2d re::operator * (const re::Vec2d& vector, float value)
{
	return re::Vec2d(vector.x * value, vector.y * value);
}


void re::Vec2d::operator += (const Vec2d& vector)
{
	x += vector.x;
	y += vector.y;
}


void re::Vec2d::operator += (float value)
{
	x += value;
	y += value;
}


void re::Vec2d::operator -= (const Vec2d& vector)
{
	x -= vector.x;
	y -= vector.y;
}


void re::Vec2d::operator -= (float value)
{
	x -= value;
	y -= value;
}


void re::Vec2d::operator *= (float value)
{
	x *= value;
	y *= value;
}


void re::Vec2d::operator /= (float value)
{
	x /= value;
	y /= value;
}


re::Vec2d::operator float* ()
{
	return d;
}


re::Vec2d::operator const float* () const
{
	return d;
}


float & re::Vec2d::operator[](size_t index)
{
	return d[index];
}


const float & re::Vec2d::operator[](size_t index) const
{
	return d[index];
}
