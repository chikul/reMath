//////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:		reVec3d.h
// Project:		Razor Edge Classes
// Description:	Definition of Vec3d class (Math Module)
// Copyright:	Copyright © 2004++ REGLabs
// Author:		Pavel Chikul
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __RE_MATH_VEC3D__
#define __RE_MATH_VEC3D__

namespace re
{
	class Matrix;

	// Vec3d Class
	class Vec3d
	{
	public:
		// Constructors
		Vec3d();
		Vec3d(const Vec3d& vector);
		Vec3d(const Vec3d* vector);
		Vec3d(float value);
		Vec3d(float xValue, float yValue, float zValue);
		Vec3d(const float* vector);

		// Destructor
		virtual ~Vec3d() = default;

	public:
		// Set vector data
		void set(const Vec3d& vector);
		void set(float value);
		void set(float xValue, float yValue, float zValue);
		void set(const float* vector);

		// Get vector magnitutde
		float length() const;

		// Parallel vectors check
		bool isParallel(const Vec3d& vector) const;

		// Normalize vector
		void normalize();

		// Nagate vector
		void negate();

		// Calculate cross product and return the result
		Vec3d cross(const Vec3d& vector) const;

		// Calculate dot product and return the result
		float dot(const Vec3d& vector) const;


		// Comparison operators
		//---------------------

		// Equal to operator - performs by value comparison of vector data
		bool operator == (const Vec3d& vector) const;

		// Not equal to operator - performs by value comparison of vector data
		bool operator != (const Vec3d& vector) const;


		// Assignment operators
		//---------------------

		// Copy assignment operator
		Vec3d& operator = (const Vec3d& vector);


		// Arithmetic operators
		//---------------------

		// Unary minus - Negates vector
		Vec3d operator - () const;

		// Returns result of two vectors addition
		Vec3d operator + (const Vec3d& vector) const;

		// Returns result of two vectors substraction
		Vec3d operator - (const Vec3d& vector) const;

		// Multiplies vector elements by value
		friend Vec3d operator * (float value, const Vec3d& vector);

		// Multiplies vector elements by value
		friend Vec3d operator * (const Vec3d& vector, float value);

		// Returns result of vector by matrix multiplication
		Vec3d operator * (const Matrix& matrix) const;

		// Returns result of vector by matrix multiplication
		Vec3d operator * (const Matrix* matrix) const;


		// Compound assignment operators
		//------------------------------

		// Vector addition
		void operator += (const Vec3d& vector);

		// Adds value to every vector component
		void operator += (float value);

		// Vector substraction
		void operator -= (const Vec3d& vector);

		// Substracts value from every vector component
		void operator -= (float value);

		// Multiplies every vector component by value
		void operator *= (float value);

		// Transforms vector by multiplying it by matrix
		void operator *= (const Matrix& matrix);

		// Transforms vector by multiplying it by matrix
		void operator *= (const Matrix* matrix);

		// Divides every vector component by value
		void operator /= (float value);


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
				float x, y, z;
			};

			float d[3];
		};
	};
}

#endif // __RE_MATH_VEC3D__
