//////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:        reVec2d.h
// Project:     reMath
// Description: Definition of Vec2d class (Math Module)
// Copyright:   Copyright © 2004++ REGLabs
// Author:      Pavel Chikul
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __RE_MATH_VEC2D__
#define __RE_MATH_VEC2D__

namespace re
{
	// Vec2d Class.
	class Vec2d
	{
	public:
		// Constructors.
		Vec2d();
		Vec2d(const Vec2d& vector);
		explicit Vec2d(const Vec2d* vector);
		explicit Vec2d(float value);
		Vec2d(float xValue, float yValue);
		explicit Vec2d(const float* vector);
		Vec2d(Vec2d&& vector) = default;

		// Destructor.
		virtual ~Vec2d() = default;

	public:
		// Set vector data.
		void set(const Vec2d& vector);
		void set(float value);
		void set(float xValue, float yValue);
		void set(const float* vector);

		// Get vector magnitutde.
		float length() const;

		// Calculate absolute distance to another vector.
		float distanceTo(const Vec2d& vector) const;

		// Parallel vectors check.
		bool isParallel(const Vec2d& vector) const;

		// Normalize vector.
		void normalize();

		// Nagate vector.
		void negate();

		// Calculate cross product and return the result.
		// Note: The cross-product of 2 vectors is only defined in 3D and 7D spaces.
		// This method computes the z-component of 2 vectors lying on the xy-plane.
		float cross(const Vec2d& vector) const;

		// Calculate dot product and return the result.
		float dot(const Vec2d& vector) const;

		// Comparison operators.
		//----------------------

		// Equal to operator - performs by value comparison of vector data.
		bool operator == (const Vec2d& vector) const;

		// Not equal to operator - performs by value comparison of vector data.
		bool operator != (const Vec2d& vector) const;

		// Assignment operators.
		//----------------------

		// Copy assignment operator.
		Vec2d& operator = (const Vec2d& vector);

		// Move assignment operator.
		Vec2d& operator = (Vec2d&& vector) = default;

		// Arithmetic operators.
		//----------------------

		// Unary minus - Negates vector.
		Vec2d operator - () const;

		// Returns result of two vector addition.
		Vec2d operator + (const Vec2d& vector) const;

		// Returns result of two vector substraction.
		Vec2d operator - (const Vec2d& vector) const;

		// Multiplies vector elements by value.
		friend Vec2d operator * (float value, const Vec2d& vector);

		// Multiplies vector elements by value.
		friend Vec2d operator * (const Vec2d& vector, float value);


		// Compound assignment operators.
		//-------------------------------

		// Vector addition.
		void operator += (const Vec2d& vector);

		// Adds value to every vector component.
		void operator += (float value);

		// Vector substraction.
		void operator -= (const Vec2d& vector);

		// Substracts value from every vector component.
		void operator -= (float value);

		// Multiplies every vector component by value.
		void operator *= (float value);

		// Divides every vector component by value.
		void operator /= (float value);


		// Conversion operators.
		//----------------------

		// Returns a pointer to vector data.
		explicit operator float* ();

		// Returns a constant pointer to vector data.
		explicit operator const float* () const;

		// Subscript operators.
		//---------------------

		// Data array access operator.
		float& operator [] (size_t index);

		// Constant data array access operator.
		const float& operator [] (size_t index) const;

	public:
		union
		{
			struct
			{
				float x, y;
			};
			float d[2];
		};
	};
}

#endif // __RE_MATH_VEC2D__
