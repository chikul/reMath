//////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:        reVec2d.h
// Project:     reMath
// Description: Definition of Vec2d class
// Copyright:   Copyright © 2004++ REGLabs
// Author:      Pavel Chikul
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __RE_MATH_VEC2D__
#define __RE_MATH_VEC2D__

namespace re
{
	/**
	 * @brief Vec2d Class.
	 */
	class Vec2d
	{
	public:
		/**
		 * @brief Default constructor.
		 */
		Vec2d();

		/**
		 * @brief Copy constructor.
		 */
		Vec2d(const Vec2d& vector);

		/**
		 * @brief Copy constructor from object pointer.
		 */
		explicit Vec2d(const Vec2d* vector);

		/**
		 * @brief Constructs a vector setting all the members to the passed value.
		 */
		explicit Vec2d(float value);

		/**
		 * @brief Constructs a vector setting all the members to the passed values.
		 */
		Vec2d(float xValue, float yValue);

		/**
		 * @brief Constructs a vector setting all the members from an array in memory.
		 */
		explicit Vec2d(const float* vector);
		
		/**
		 * @brief Move constructor.
		 */
		Vec2d(Vec2d&& vector) = default;

		/**
		 * @brief Destructor.
		 */
		virtual ~Vec2d() = default;

		/**
		 * @brief Set vector data.
		 */
		void set(const Vec2d& vector);

		/**
		 * @brief Set vector data.
		 */
		void set(float value);

		/**
		 * @brief Set vector data.
		 */
		void set(float xValue, float yValue);

		/**
		 * @brief Set vector data.
		 */
		void set(const float* vector);

		/**
		 * @brief Get vector magnitutde.
		 */
		float length() const;

		/**
		 * @brief Calculate absolute distance to another vector.
		 */
		float distanceTo(const Vec2d& vector) const;

		/**
		 * @brief Parallel vectors check.
		 */
		bool isParallel(const Vec2d& vector) const;

		/**
		 * @brief Normalize vector.
		 */
		void normalize();

		/**
		 * @brief Nagate vector.
		 */
		void negate();

		/**
		 * @brief Calculate cross product and return the result.
		 * Note: The cross-product of 2 vectors is only defined in 3D and 7D spaces.
		 * This method computes the z-component of 2 vectors lying on the xy-plane.
		 */
		float cross(const Vec2d& vector) const;

		/**
		 * @brief Calculate dot product and return the result.
		 */
		float dot(const Vec2d& vector) const;

		// Comparison operators.
		//----------------------

		/**
		 * @brief Equal to operator - performs by value comparison of vector data.
		 */
		bool operator == (const Vec2d& vector) const;

		/**
		 * @brief Not equal to operator - performs by value comparison of vector data.
		 */
		bool operator != (const Vec2d& vector) const;

		// Assignment operators.
		//----------------------

		/**
		 * @brief Copy assignment operator.
		 */
		Vec2d& operator = (const Vec2d& vector);

		/**
		 * @brief Move assignment operator.
		 */
		Vec2d& operator = (Vec2d&& vector) = default;

		// Arithmetic operators.
		//----------------------

		/**
		 * @brief Unary minus - Negates vector.
		 */
		Vec2d operator - () const;

		/**
		 * @brief Returns result of two vector addition.
		 */
		Vec2d operator + (const Vec2d& vector) const;

		/**
		 * @brief Returns result of two vector substraction.
		 */
		Vec2d operator - (const Vec2d& vector) const;

		/**
		 * @brief Multiplies vector elements by value.
		 */
		friend Vec2d operator * (float value, const Vec2d& vector);

		/**
		 * @brief Multiplies vector elements by value.
		 */
		friend Vec2d operator * (const Vec2d& vector, float value);


		// Compound assignment operators.
		//-------------------------------

		/**
		 * @brief Vector addition.
		 */
		void operator += (const Vec2d& vector);

		/**
		 * @brief Adds value to every vector component.
		 */
		void operator += (float value);

		/**
		 * @brief Vector substraction.
		 */
		void operator -= (const Vec2d& vector);

		/**
		 * @brief Substracts value from every vector component.
		 */
		void operator -= (float value);

		/**
		 * @brief Multiplies every vector component by value.
		 */
		void operator *= (float value);

		/**
		 * @brief Divides every vector component by value.
		 */
		void operator /= (float value);


		// Conversion operators.
		//----------------------

		/**
		 * @brief Returns a pointer to vector data.
		 */
		explicit operator float* ();

		/**
		 * @brief Returns a constant pointer to vector data.
		 */
		explicit operator const float* () const;

		// Subscript operators.
		//---------------------

		/**
		 * @brief Data array access operator.
		 */
		float& operator [] (size_t index);

		/**
		 * @brief Constant data array access operator.
		 */
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
