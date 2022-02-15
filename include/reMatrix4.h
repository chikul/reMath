//////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:        reMatrix4.h
// Project:     reMath
// Description: Definition of Matrix4 class (Math Module)
// Copyright:   Copyright © 2004++ REGLabs
// Author:      Pavel Chikul
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __RE_MATH_MATRIX4__
#define __RE_MATH_MATRIX4__

namespace re
{
	class Vec3d;
	class Matrix3;
	class Quaternion;

	// Matrix4 Class.
	class Matrix4
	{
	public:
		// Constructors.
		Matrix4();
		explicit Matrix4(const Matrix4& matrix);
		explicit Matrix4(const Matrix4* matrix);
		explicit Matrix4(const float* matrix);
		explicit Matrix4(const Matrix3& matrix);
		Matrix4(Matrix4&& matrix) = default;

		// Destructor.
		virtual ~Matrix4() = default;

	public:
		// Load NULL matrix.
		void loadIdentity();

		// Set matrix data (passing 0 will load identity).
		void set(const float* matrix);

		// Set rotation angles (in radians).
		void setRotation(float x, float y, float z);
		void setRotation(const float* r);
		void setRotation(const Vec3d& r);

		// Set translation vector.
		void setTranslation(float x, float y, float z);
		void setTranslation(const float* t);
		void setTranslation(const Vec3d& t);

		// Get translation vector.
		Vec3d getTranslation() const;

		// Set scaling values.
		void setScale(float x, float y, float z);
		void setScale(const Vec3d& s);
		void setScale(float scale);

		// Get scaling value.
		float getScale() const;

		// Get euler rotation angles (in radians).
		Vec3d getEulers() const;

		// Get matrix coordinate system's Center coordinates.
		Vec3d getCenter() const;

		// Get matrix coordinate system's X-axis vector coordinates.
		Vec3d xAxis() const;

		// Get matrix coordinate system's Y-axis vector coordinates.
		Vec3d yAxis() const;

		// Get matrix coordinate system's z-axis vector coordinates.
		Vec3d zAxis() const;

		// Inverse matrix.
		void inverse();

		// Transpose matrix.
		void transpose();

		// Returns inversed matrix leaving original intact.
		Matrix4 toInversed() const;

		// Returns transposed matrix leaving original intact.
		Matrix4 toTransposed() const;

		// Apply matrix rotation to a vactor.
		void rotate(float& x, float& y, float& z) const;
		void rotate(float* vector) const;
		void rotate(Vec3d& vector) const;

		// Apply inverse matrix rotation to a vactor.
		void inverseRotate(float& x, float& y, float& z) const;
		void inverseRotate(float* vector) const;
		void inverseRotate(Vec3d& vector) const;

		// Apply matrix translation to a vactor.
		void translate(float& x, float& y, float& z) const;
		void translate(float* vector) const;
		void translate(Vec3d& vector) const;

		// Apply inverse matrix translation to a vactor.
		void inverseTranslate(float& x, float& y, float& z) const;
		void inverseTranslate(float* vector) const;
		void inverseTranslate(Vec3d& vector) const;

		// Apply matrix scale to a vactor.
		void scale(float &x, float &y, float &z) const;
		void scale(float* vector) const;
		void scale(Vec3d& vector) const;

		// Apply inverse matrix scale to a vactor.
		void inverseScale(float& x, float& y, float& z) const;
		void inverseScale(float* vector) const;
		void inverseScale(Vec3d& vector) const;

		Matrix3 rotationMatrix() const;

		// Comparison operators.
		//----------------------

		// Equal to operator - performs by byte comparison of matrices data.
		bool operator == (const Matrix4& matrix) const;

		// Not equal to operator - performs by byte comparison of matrices data.
		bool operator != (const Matrix4& matrix) const;


		// Assignment operators.
		//----------------------

		// Copy assignment operator.
		Matrix4& operator = (const Matrix4& matrix);

		// Move assignment operator.
		Matrix4& operator = (Matrix4&& matrix) = default;


		// Arithmetic operators.
		//----------------------

		// Returns result of matrices multiplication.
		Matrix4 operator * (const Matrix4& matrix) const;

		Quaternion operator * (const Quaternion& q) const;


		// Compound assignment operators.
		//-------------------------------

		// Performs matrices multiplication
		void operator *= (const Matrix4& matrix);


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
		float data_[16];
	};
}

#endif // __RE_MATH_MATRIX__
