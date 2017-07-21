//////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:		reMathUtil.cpp
// Project:		Razor Edge Classes
// Description:	Implementation of Razor Edge math utility functions (Math Module)
// Copyright:	Copyright © 2004++ REGLabs
// Author:		Pavel Chikul
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "reMathUtil.h"
#include "reMath.h"
#include <string.h>
#include <math.h>

float re::toRadians(float degrees)
{
	return degrees * PI / 180.f;
}



float re::toDegrees(float radians)
{
	return radians / PI / 180.f;
}



unsigned long re::maxPowerOfTwo(unsigned long value)
{
	unsigned long power = 1;
	unsigned long result = 0;

	while (power < value)
	{
		power <<= 1;
		result++;
	}

	return result;
}



unsigned char re::getHighNibble(unsigned char byte)
{
	return byte & 0xF0;
}



unsigned char re::getLowNibble(unsigned char byte)
{
	return byte & 0x0F;
}



re::Matrix re::perspective(float fovy, float aspect, float zNear, float zFar)
{
	float matrix[16];
	memset(matrix, 0, sizeof(matrix));

	float cotngentHalfFovy = float(1.f / (tan(toRadians(fovy) / 2.f)));

	matrix[0] = cotngentHalfFovy / aspect;
	matrix[5] = cotngentHalfFovy;
	matrix[10] = (zFar + zNear) / (zNear - zFar);
	matrix[11] = -1.f;
	matrix[14] = (2.f * zFar * zNear) / (zNear - zFar);

	return Matrix(matrix);
}
