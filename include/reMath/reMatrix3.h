//////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:        reMatrix3.h
// Project:     reMath
// Description: Definition of Matrix3 class
// Copyright:   Copyright © 2004++ REGLabs
// Author:      Pavel Chikul
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __RE_MATH_MATRIX3__
#define __RE_MATH_MATRIX3__

namespace re
{
	class Vec3d;
	class Matrix4;

	/*
	 * @brief Matrix3 Class.
	 */
	class Matrix3
	{
	public:
		// Constructors.
		Matrix3();
		explicit Matrix3(const Matrix3& matrix);
		explicit Matrix3(const Matrix3* matrix);
		explicit Matrix3(const float* matrix);
		explicit Matrix3(const Matrix4& matrix);
		Matrix3(Matrix3&& matrix) = default;

		// Destructor.
		virtual ~Matrix3() = default;

	public:
		// Load NULL matrix.
		void loadIdentity();

		// Set matrix data (passing 0 will load identity).
		void set(const float* matrix);

		// Set rotation angles (in radians).
		void setRotation(float x, float y, float z);
		void setRotation(const float* r);
		void setRotation(const Vec3d& r);

		// Get euler rotation angles (in radians).
		Vec3d getEulers() const;

		// Get matrix coordinate system's Center coordinates
		/*Vec3d getCenter() const;

		// Get matrix coordinate system's X-axis vector coordinates
		Vec3d xAxis() const;

		// Get matrix coordinate system's Y-axis vector coordinates
		Vec3d yAxis() const;

		// Get matrix coordinate system's z-axis vector coordinates
		Vec3d zAxis() const;

		// Inverse matrix
		void inverse();

		// Transpose matrix
		void transpose();

		// Returns inversed matrix leaving original intact
		Matrix3 toInversed() const;

		// Returns transposed matrix leaving original intact
		Matrix3 toTransposed() const;*/

		// Apply matrix rotation to a vactor.
		void rotate(float& x, float& y, float& z) const;
		void rotate(float* vector) const;
		void rotate(Vec3d& vector) const;

		// Apply inverse matrix rotation to a vactor.
		void inverseRotate(float& x, float& y, float& z) const;
		void inverseRotate(float* vector) const;
		void inverseRotate(Vec3d& vector) const;

		// Apply matrix scale to a vactor
		/*void scale(float &x, float &y, float &z) const;
		void scale(float* vector) const;
		void scale(Vec3d& vector) const;

		// Apply inverse matrix scale to a vactor
		void inverseScale(float& x, float& y, float& z) const;
		void inverseScale(float* vector) const;
		void inverseScale(Vec3d& vector) const;*/

		// Comparison operators.
		//----------------------

		// Equal to operator - performs by byte comparison of matrices data.
		bool operator == (const Matrix3& matrix) const;

		// Not equal to operator - performs by byte comparison of matrices data.
		bool operator != (const Matrix3& matrix) const;


		// Assignment operators.
		//----------------------

		// Copy assignment operator.
		Matrix3& operator = (const Matrix3& matrix);

		// Move assignment operator.
		Matrix3& operator = (Matrix3&& matrix) = default;


		// Arithmetic operators.
		//----------------------

		// Returns result of matrices multiplication.
		/*Matrix3 operator * (const Matrix3& matrix);


		// Compound assignment operators.
		//-------------------------------

		// Performs matrices multiplication.
		void operator *= (const Matrix3& matrix);*/


		// Conversion operators.
		//----------------------

		// Returns a pointer to matrix data.
		explicit operator float* ();

		// Returns a constant pointer to matrix data.
		explicit operator const float* () const;

		// Subscript operators.
		//---------------------

		// Data array access operator.
		float& operator [] (size_t index);

		// Constant data array access operator.
		const float& operator [] (size_t index) const;

	private:
		float data_[9];
	};
}

#endif // __RE_MATH_MATRIX3__
