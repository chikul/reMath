//////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:        reQuaternion.h
// Project:     Razor Edge Classes
// Description: Definition of Quaternion class (Math Module)
// Copyright:   Copyright © 2004++ REGLabs
// Author:      Pavel Chikul
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __RE_MATH_QUATERNION__
#define __RE_MATH_QUATERNION__

namespace re
{
	class Vec3d;
	class Matrix4;

	// Quaternion Class
	class Quaternion
	{
	public:
		// Constructors
		Quaternion();
		Quaternion(const Quaternion& quaternion);
		Quaternion(const Quaternion* quaternion);
		Quaternion(float xValue, float yValue, float zValue, float wValue);
		Quaternion(const float* quaternion);

		// Destructor
		virtual ~Quaternion() = default;

	public:
		// Set quaternion data
		void set(const Quaternion& quaternion);
		void set(float xValue, float yValue, float zValue, float wValue);
		void set(const float* quaternion);

		// Set quaternion data from three components (X, Y, Z) and calculate W
		void set(float xValue, float yValue, float zValue);
		void set(const Vec3d& vector);

		// Get quaternion from Euler angles
		static Quaternion fromEulers(Vec3d& vector);
		static Quaternion fromEulerXRotation(float angle);
		static Quaternion fromEulerYRotation(float angle);
		static Quaternion fromEulerZRotation(float angle);

		// Calculate the W component when only X, Y, and Z are given
		void computeW();

		// Calculate Euler angles from quaternion data
		Vec3d getEulers() const;

		// Get rotation matrix from quaternion data
		Matrix4 getMatrix() const; // TODO: Check ToMatrix in book

		// Get quaternion magnitutde
		float length() const;

		// Normalize quaternion
		void normalize();

		// Negate quaternion
		void negate();

		// Return the result of Spherical Linear Interpolation between two quaternions scaled by factor
		Quaternion slerp(const Quaternion& quaternion, float scale) const;

		// Return the result of Linear Interpolation between two quaternions scaled by factor
		Quaternion lerp(const Quaternion& quaternion, float scale) const;

		// Calculate dot product and return the result
		float dot(const Quaternion& quaternion) const;


		// Comparison operators
		//---------------------

		// Equal to operator - performs by value comparison of quaternion data
		bool operator == (const Quaternion& quaternion) const;

		// Not equal to operator - performs by value comparison of quaternion data
		bool operator != (const Quaternion& quaternion) const;


		// Assignment operators
		//---------------------

		// Copy assignment operator
		Quaternion& operator = (const Quaternion& quaternion);


		// Arithmetic operators
		//---------------------

		// Unary minus - Negates quaternion
		Quaternion operator - () const;

		// Returns result of two quaternions addition
		Quaternion operator + (const Quaternion& quaternion) const;

		// Returns result of two quaternions substraction
		Quaternion operator - (const Quaternion& quaternion) const;

		// Returns result of two quaternions multiplication
		Quaternion operator * (const Quaternion& quaternion) const;

		// Multiplies quaternion elements by value
		friend Quaternion operator * (float value, const Quaternion& quaternion);

		// Multiplies quaternion elements by value
		friend Quaternion operator * (const Quaternion& quaternion, float value);

		// Divides quaternion elements by value
		Quaternion operator / (float value) const;


		// Compound assignment operators
		//------------------------------

		// Quaternion addition
		Quaternion& operator += (const Quaternion& quaternion);

		// Quaternion substraction
		Quaternion& operator -= (const Quaternion& quaternion);

		// Quaternion multiplication
		Quaternion& operator *= (const Quaternion& quaternion);

		// Quaternion multiplication by value
		Quaternion& operator *= (float value);

		// Quaternion substraction by value
		Quaternion& operator /= (float value);


		// Conversion operators
		//---------------------

		// Returns a pointer to vector data
		operator float* ();

		// Returns a constant pointer to vector data
		operator const float* () const;

	public:
		union
		{
			struct
			{
				float x, y, z, w;
			};
			float d[4];
		};
	};
}

#endif // __RE_MATH_QUATERNION__
