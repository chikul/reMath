//////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:		reMatrix.h
// Project:		Razor Edge Classes
// Description:	Definition of Matrix class (Math Module)
// Copyright:	Copyright © 2004++ REGLabs
// Author:		Pavel Chikul
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __RE_MATH_MATRIX__
#define __RE_MATH_MATRIX__

namespace re
{
	class Vec3d;

	// Matrix Class
	class Matrix
	{
	public:
		// Constructors
		Matrix();
		Matrix(const Matrix& matrix);
		Matrix(const Matrix* matrix);
		Matrix(const float* matrix);

		// Destructor
		virtual ~Matrix() = default;

	public:
		// Load NULL matrix
		void loadIdentity();

		// Set matrix data (passing 0 will load identity)
		void set(const float* matrix);

		// Set rotation angles (in radians)
		void setRotation(float x, float y, float z);
		void setRotation(const float* r);
		void setRotation(const Vec3d& r);

		// Set translation vector
		void setTranslation(float x, float y, float z);
		void setTranslation(const float* t);
		void setTranslation(const Vec3d& t);

		// Get translation vector
		Vec3d getTranslation() const;

		// Set scaling values
		void setScale(float x, float y, float z);
		void setScale(const Vec3d& s);
		void setScale(float scale);

		// Get scaling value
		float getScale() const;

		// Get euler rotation angles (in radians)
		Vec3d getEulers() const;

		// Get matrix coordinate system's Center coordinates
		Vec3d getCenter() const;

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
		Matrix toInversed() const;

		// Returns transposed matrix leaving original intact
		Matrix toTransposed() const;

		// Apply matrix rotation to a vactor
		void rotate(float& x, float& y, float& z) const;
		void rotate(float* vector) const;
		void rotate(Vec3d& vector) const;

		// Apply inverse matrix rotation to a vactor
		void inverseRotate(float& x, float& y, float& z) const;
		void inverseRotate(float* vector) const;
		void inverseRotate(Vec3d& vector) const;

		// Apply matrix translation to a vactor
		void translate(float& x, float& y, float& z) const;
		void translate(float* vector) const;
		void translate(Vec3d& vector) const;

		// Apply inverse matrix translation to a vactor
		void inverseTranslate(float& x, float& y, float& z) const;
		void inverseTranslate(float* vector) const;
		void inverseTranslate(Vec3d& vector) const;

		// Apply matrix scale to a vactor
		void scale(float &x, float &y, float &z) const;
		void scale(float* vector) const;
		void scale(Vec3d& vector) const;

		// Apply inverse matrix scale to a vactor
		void inverseScale(float& x, float& y, float& z) const;
		void inverseScale(float* vector) const;
		void inverseScale(Vec3d& vector) const;

		// Comparison operators
		//---------------------

		// Equal to operator - performs by byte comparison of matrices data
		bool operator == (const Matrix& matrix);

		// Not equal to operator - performs by byte comparison of matrices data
		bool operator != (const Matrix& matrix);


		// Assignment operators
		//---------------------

		// Copy assignment operator
		Matrix& operator = (const Matrix& matrix);


		// Arithmetic operators
		//---------------------

		// Returns result of matrices multiplication
		Matrix operator * (const Matrix& matrix);


		// Compound assignment operators
		//------------------------------

		// Performs matrices multiplication
		void operator *= (const Matrix& matrix);


		// Conversion operators
		//---------------------

		// Returns a pointer to matrix data
		operator float* ();

		// Returns a constant pointer to matrix data
		operator const float* () const;

	private:
		float data_[16];
	};
}

#endif // __RE_MATH_MATRIX__
