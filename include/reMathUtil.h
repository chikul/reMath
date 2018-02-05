//////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:        reMathUtil.h
// Project:     Razor Edge Classes
// Description: Definition of Razor Edge math utility functions (Math Module)
// Copyright:   Copyright © 2004++ REGLabs
// Author:      Pavel Chikul
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __RE_MATH_UTIL__
#define __RE_MATH_UTIL__

namespace re
{
	// PI Value.
	const float PI = 3.14159265358979f;
	const float PI2 = 6.28318530717959f;

	class Vec3d;
	class Matrix4;

	// Converts degrees to radians.
	float toRadians(float degrees);

	// Converts radians to degrees.
	float toDegrees(float radians);

	// Returns a maximum power of two which is inside the passed value.
	// Example: 7 will be returned for 200, as 2^7 == 128 is the max power of 2 inside 200.
	unsigned long maxPowerOfTwo(unsigned long value);

	// Get higher half of the byte.
	unsigned char getHighNibble(unsigned char byte);

	// Get lower half of the byte
	unsigned char getLowNibble(unsigned char byte);

	// Returns a perspective projection matrix.
	// <param name="fovy">Field of view angle, in degrees, in the y direction</param>
	// <param name="aspect">Aspect ratio is the ratio of x (width) to y (height)</param>
	// <param name="zNear">distance from the viewer to the near clipping plane (always positive)</param>
	// <param name="zFar">distance from the viewer to the far clipping plane (always positive)</param>
	// <returns>Perspective projection matrix</returns>
	Matrix4 perspective(float fovy, float aspect, float zNear = 0.1f, float zFar = 10000.0f);

	// Returns a view matrix composed of eye coordinates, view center, and the up-vector.
	Matrix4 lookAt(const Vec3d& eye, const Vec3d& center, const Vec3d& up);
}

#endif // __RE_MATH_UTIL__
