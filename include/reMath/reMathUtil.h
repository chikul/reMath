//////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:        reMathUtil.h
// Project:     reMath
// Description: Definition of Razor Edge math utility functions
// Copyright:   Copyright © 2004++ REGLabs
// Author:      Pavel Chikul
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __RE_MATH_UTIL__
#define __RE_MATH_UTIL__

namespace re
{
	/**
	 * @brief PI Value.
	 */
	const float PI = 3.14159265358979f;
	const float PI2 = 6.28318530717959f;

	class Vec3d;
	class Matrix4;

	/**
	 * @brief Converts degrees to radians.
	 * 
	 * @param degrees Angle in degrees
	 * @return Angle in radians
	 */
	float toRadians(float degrees);

	/** 
	 * @brief Converts radians to degrees.
	 *
	 * @param radians Angle in radians
	 * @return Angle in degrees
	 */
	float toDegrees(float radians);

	/**
	 * @brief Returns a maximum power of two which is inside the passed value. 
	 * Example: 7 will be returned for 200, as 2^7 == 128 is the max power of 2 inside 200.
	 * 
	 * @param value Value to test
	 * @return Maximum power of two inside tested value
	 */
	unsigned long maxPowerOfTwo(unsigned long value);

	/*
	 * @brief Get higher half of the byte.
	 * 
	 * @param byte A byte to extract the high nibble from
	 * @return High nibble of a byte
	 */
	unsigned char getHighNibble(unsigned char byte);

    /**
	 * @brief Get lower half of the byte.
	 * 
	 * @param byte A byte to extract the low nibble from
	 * @return Low nibble of a byte
	 */
	unsigned char getLowNibble(unsigned char byte);

    /**
	 * @brief Calculates a perspective projection matrix.
	 *
	 * @param fovy Field of view angle, in degrees, in the y direction
	 * @param aspect Aspect ratio is the ratio of x (width) to y (height)
	 * @param zNear Distance from the viewer to the near clipping plane (always positive)
	 * @param zFar Distance from the viewer to the far clipping plane (always positive)
	 * @return Perspective projection matrix
	 */
	Matrix4 perspective(float fovy, float aspect, float zNear = 0.1f, float zFar = 10000.0f);

	/** 
	 * @brief Returns a view matrix composed of eye coordinates, view center, and the up-vector.
	 * 
	 * @param eye Eye position
	 * @param center View center position
	 * @param up Up direction vector
	 * @return View matrix
	 */
	Matrix4 lookAt(const Vec3d& eye, const Vec3d& center, const Vec3d& up);

    /**
	 * @brief Calculates the area of a triangle defined by three vertices in 3D space.
	 *
	 * @param a First vertex
	 * @param b Second vertex
	 * @param c Third vertex
	 * @return Triangle area
	 */
	float triangleArea(const Vec3d& a, const Vec3d& b, const Vec3d& c);
}

#endif // __RE_MATH_UTIL__
