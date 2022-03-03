//////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:        reMathUtil.cpp
// Project:     reMath
// Description: Implementation of Razor Edge math utility functions
// Copyright:   Copyright © 2004++ REGLabs
// Author:      Pavel Chikul
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "reMath/reMathUtil.h"
#include "reMath/reMath.h"
#include <cmath>

float re::toRadians(float degrees)
{
	return degrees * PI / 180.f;
}


float re::toDegrees(float radians)
{
	return radians * 180.f / PI;
}


unsigned long re::maxPowerOfTwo(unsigned long value)
{
	if (!value)
		return 0;

	unsigned long result = 0;
	while (value)
	{
		value = value >> 1;
		result++;
	}

	return --result;
}


unsigned char re::getHighNibble(unsigned char byte)
{
	return byte & 0xF0;
}


unsigned char re::getLowNibble(unsigned char byte)
{
	return byte & 0x0F;
}


re::Matrix4 re::perspective(float fovy, float aspect, float zNear, float zFar)
{
	const float tanHalfFovy = 1.f / tan(toRadians(fovy) / 2.f);

	Matrix4 matrix;
	matrix[0] = tanHalfFovy / aspect;
	matrix[5] = tanHalfFovy;
	matrix[10] = (zFar + zNear) / (zNear - zFar);
	matrix[11] = -1.f;
	matrix[14] = (2.f * zFar * zNear) / (zNear - zFar);
	return matrix;
}


re::Matrix4 re::lookAt(const Vec3d& eye, const Vec3d& center, const Vec3d& up)
{
	// Calculate forward vector
	Vec3d forward(center - eye);
	forward.normalize();

	// Normalize up vector
	Vec3d upVector(up);
	upVector.normalize();

	// Get the perpendicular "side" vector
	Vec3d side(forward.cross(up));
	side.normalize();

	// Recompute up as "side x forward"
	upVector = side.cross(forward);

	Matrix4 matrix2, result;
	
	// Column #1
	matrix2[0] = side.x;
	matrix2[4] = side.y;
	matrix2[8] = side.z;

	// Column #2
	matrix2[1] = upVector.x;
	matrix2[5] = upVector.y;
	matrix2[9] = upVector.z;

	// Column #3
	matrix2[2] = -forward.x;
	matrix2[6] = -forward.y;
	matrix2[10] = -forward.z;

	// Set eye translation
	result *= matrix2;
	result.setTranslation(-eye);
	
	return result;
}


float re::triangleArea(const Vec3d & a, const Vec3d & b, const Vec3d & c)
{
	const float d1 = a.distanceTo(b);
	const float d2 = a.distanceTo(c);
	const float d3 = b.distanceTo(c);
	const float halfPerimeter = (d1 + d2 + d3) / 2;
	return sqrt(halfPerimeter * (halfPerimeter - d1) * (halfPerimeter - d2) * (halfPerimeter - d3));
}
