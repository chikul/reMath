//////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:		reVec3d.cpp
// Project:		Razor Edge Classes
// Description:	Implementation of Vec3d class (Math Module)
// Copyright:	Copyright © 2004++ REGLabs
// Author:		Pavel Chikul
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "reVec3d.h"
#include "reMatrix.h"
#include <string.h>
#include <math.h>

re::Vec3d::Vec3d()
{
	memset(d, 0, sizeof(d));
}



re::Vec3d::Vec3d(const Vec3d& vector)
{
	set(vector);
}



re::Vec3d::Vec3d(const Vec3d* vector)
{
	set(vector->d);
}



re::Vec3d::Vec3d(float value)
{
	set(value);
}



re::Vec3d::Vec3d(float xValue, float yValue, float zValue)
{
	set(xValue, yValue, zValue);
}



re::Vec3d::Vec3d(const float* vector)
{
	set(vector);
}



void re::Vec3d::set(const Vec3d& vector)
{
	memcpy(&d, vector.d, sizeof(d));
}



void re::Vec3d::set(float value)
{
	x = value;
	y = value;
	z = value;
}



void re::Vec3d::set(float xValue, float yValue, float zValue)
{
	x = xValue;
	y = yValue;
	z = zValue;
}



void re::Vec3d::set(const float* vector)
{
	memcpy(&d, vector, sizeof(d));
}



float re::Vec3d::length() const
{
	return sqrtf(x * x + y * y + z * z);
}



bool re::Vec3d::isParallel(const Vec3d& vector) const
{
	return (((x / vector.x) == (y / vector.y)) && 
		((x / vector.x) == (z / vector.z)));
}



void re::Vec3d::normalize()
{
	float d = length();

	if (d)
	{
		x /= d;
		y /= d;
		z /= d;
	}
	else
	{
		set(0, 0, 0);
	}
}



void re::Vec3d::negate()
{
	x = -x;
	y = -y;
	z = -z;
}



re::Vec3d re::Vec3d::cross(const Vec3d& vector) const
{
	return Vec3d((y * vector.z - z * vector.y), (z * vector.x - x * vector.z), (x * vector.y - y * vector.x));
}



float re::Vec3d::dot(const Vec3d& vector) const
{
	return (x * vector.x + y * vector.y + z * vector.z);
}



bool re::Vec3d::operator == (const Vec3d& vector) const
{
	return (x == vector.x && y == vector.y && z == vector.z);
}



bool re::Vec3d::operator != (const Vec3d& vector) const
{
	return (x != vector.x || y != vector.y || z != vector.z);
}



re::Vec3d& re::Vec3d::operator = (const Vec3d& vector)
{
	if (&vector != this)
		memcpy(d, vector.d, sizeof(d));

	return *this;
}



re::Vec3d re::Vec3d::operator - () const
{
	Vec3d result(this);
	result.negate();
	return result;
}



re::Vec3d re::Vec3d::operator + (const Vec3d& vector) const
{
	return Vec3d(x + vector.x, y + vector.y, z + vector.z);
}



re::Vec3d re::Vec3d::operator - (const Vec3d& vector) const
{
	return Vec3d(x - vector.x, y - vector.y, z - vector.z);
}



re::Vec3d operator * (float value, const re::Vec3d& vector)
{
	return re::Vec3d(vector.x * value, vector.y * value, vector.z * value);
}



re::Vec3d operator * (const re::Vec3d& vector, float value)
{
	return re::Vec3d(vector.x * value, vector.y * value, vector.z * value);
}



re::Vec3d re::Vec3d::operator * (const re::Matrix& matrix) const
{
	const float* data = matrix;
	return re::Vec3d(
		(x*data[0] + y*data[4] + z*data[8] + data[12]),
		(x*data[1] + y*data[5] + z*data[9] + data[13]),
		(x*data[2] + y*data[6] + z*data[10] + data[14]));
}



re::Vec3d re::Vec3d::operator * (const Matrix* matrix) const
{
	if (!matrix)
		return re::Vec3d();

	const float* data = (Matrix)matrix;
	return re::Vec3d(
		(x*data[0] + y*data[4] + z*data[8] + data[12]),
		(x*data[1] + y*data[5] + z*data[9] + data[13]),
		(x*data[2] + y*data[6] + z*data[10] + data[14]));
}



void re::Vec3d::operator += (const Vec3d& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;
}



void re::Vec3d::operator += (float value)
{
	x += value;
	y += value;
	z += value;
}



void re::Vec3d::operator -= (const Vec3d& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
}



void re::Vec3d::operator -= (float value)
{
	x -= value;
	y -= value;
	z -= value;
}



void re::Vec3d::operator *= (float value)
{
	x *= value;
	y *= value;
	z *= value;
}



void re::Vec3d::operator *= (const Matrix& matrix)
{
	double newValues[3];
	const float* data = matrix;

	newValues[0] = x*data[0] + y*data[4] + z*data[8] + data[12];
	newValues[1] = x*data[1] + y*data[5] + z*data[9] + data[13];
	newValues[2] = x*data[2] + y*data[6] + z*data[10] + data[14];

	x = (float)newValues[0];
	y = (float)newValues[1];
	z = (float)newValues[2];
}



void re::Vec3d::operator *= (const Matrix* matrix)
{
	if (!matrix)
		return;

	double newValues[3];
	const float* data = (Matrix)matrix;

	newValues[0] = x*data[0] + y*data[4] + z*data[8] + data[12];
	newValues[1] = x*data[1] + y*data[5] + z*data[9] + data[13];
	newValues[2] = x*data[2] + y*data[6] + z*data[10] + data[14];

	x = (float)newValues[0];
	y = (float)newValues[1];
	z = (float)newValues[2];
}



void re::Vec3d::operator /= (float value)
{
	x /= value;
	y /= value;
	z /= value;
}



re::Vec3d::operator float* ()
{
	return d;
}



re::Vec3d::operator const float* () const
{
	return d;
}
