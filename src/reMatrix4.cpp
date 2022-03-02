//////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:        reMatrix4.cpp
// Project:     reMath
// Description: Implementation of Matrix4 class
// Copyright:   Copyright © 2004++ REGLabs
// Author:      Pavel Chikul
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "reMath/reMatrix4.h"
#include "reMath/reVec3d.h"
#include "reMath/reMatrix3.h"
#include "reMath/reQuaternion.h"
#include "reMath/reMathUtil.h"
#include <cstring>
#include <cmath>

re::Matrix4::Matrix4()
{
	loadIdentity();
}



re::Matrix4::Matrix4(const Matrix4& matrix)
{
	if (&matrix == this)
		return;

	memcpy(data_, matrix.data_, sizeof(float) * 16);
}



re::Matrix4::Matrix4(const Matrix4* matrix)
{
	if (matrix == this || !matrix)
		return;

	memcpy(data_, matrix->data_, sizeof(float) * 16);
}



re::Matrix4::Matrix4(const float* matrix)
{
	if (!matrix)
	{
		loadIdentity();
		return;
	}

	memcpy(data_, matrix, sizeof(float) * 16);
}

re::Matrix4::Matrix4(const Matrix3 & matrix)
{
	loadIdentity();
	memcpy(&data_[0], &matrix[0], sizeof(float) * 3);
	memcpy(&data_[4], &matrix[3], sizeof(float) * 3);
	memcpy(&data_[8], &matrix[6], sizeof(float) * 3);
}



void re::Matrix4::loadIdentity()
{
	memset(data_, 0, sizeof(float) * 16);
	data_[0] = data_[5] = data_[10] = data_[15] = 1;
}



void re::Matrix4::set(const float* matrix)
{
	if (!matrix)
	{
		loadIdentity();
		return;
	}

	memcpy(data_, matrix, sizeof(float) * 16);
}



void re::Matrix4::setRotation(float x, float y, float z)
{
	const float cx = cos(x);						//	| 0  1  2  3|		|0-0  0-1  0-2  0-3|
	const float sx = sin(x);						//	| 4  5  6  7|		|1-0  1-1  1-2  1-3|
	const float cy = cos(y);						//	| 8  9 10 11|		|2-0  2-1  2-2  2-3|
	const float sy = sin(y);						//	|12 13 14 15|		|3-0  3-1  3-2  3-3|
	const float cz = cos(z);
	const float sz = sin(z);						//	| 0  4  8 12|
	const float sxsy = sx * sy;						//	| 1	 5  9 13|
	const float cxsy = cx * sy;						//	| 2  6 10 14|
													//	| 3  7 11 15|
	data_[0] = cy * cz;						/* 0-0 \                      */
	data_[1] = cy * sz;						/* 0-1	|- top row, 1-3 col.  */
	data_[2] = -sy;							/* 0-2 /                      */

	data_[4] = sxsy * cz - cx * sz;			/* 1-0 \                      */
	data_[5] = sxsy * sz + cx * cz;			/* 1-1  |- 2-nd row, 1-3 col. */
	data_[6] = sx * cy;						/* 1-2 /                      */

	data_[8] = cxsy * cz + sx * sz;			/* 2-0 \                      */
	data_[9] = cxsy * sz - sx * cz;			/* 2-1  |- 3-rd row, 1-3 col. */
	data_[10] = cx * cy;					/* 2-2 /                      */
}



void re::Matrix4::setRotation(const float* r)
{
	setRotation(r[0], r[1], r[2]);
}



void re::Matrix4::setRotation(const Vec3d& r)
{
	setRotation(r.x, r.y, r.z);
}



void re::Matrix4::setTranslation(float x, float y, float z)
{
	data_[12] = x;	// 3-0
	data_[13] = y;	// 3-1
	data_[14] = z;	// 3-2
}



void re::Matrix4::setTranslation(const float* t)
{
	memcpy(&data_[12], t, sizeof(float) * 3);
}



void re::Matrix4::setTranslation(const re::Vec3d& t)
{
	memcpy(&data_[12], t.d, sizeof(float) * 3);
}



re::Vec3d re::Matrix4::getTranslation() const
{
	return Vec3d(data_[12], data_[13], data_[14]);
}



void re::Matrix4::setScale(float x, float y, float z)
{
	data_[0] = x;
	data_[5] = y;
	data_[10] = z;
}



void re::Matrix4::setScale(const Vec3d& s)
{
	data_[0] = s.x;
	data_[5] = s.y;
	data_[10] = s.z;
}



void re::Matrix4::setScale(const float scale)
{
	data_[0] = scale;
	data_[5] = scale;
	data_[10] = scale;
}



float re::Matrix4::getScale() const
{
	return 1 / data_[0];
}



re::Vec3d re::Matrix4::getEulers() const
{
	//#pragma TODO("Add valid range checks at least for asinf() (errno)")
	Vec3d result;

	if (data_[1] > 0.9998) // singularity at north pole
	{
		result.y = atan2(data_[8], data_[10]);
		result.z = PI / 2;
		result.x = 0;
	}
	else if (data_[1] < -0.9998) // singularity at south pole
	{
		result.y = atan2(data_[8], data_[10]);
		result.z = -PI / 2;
		result.x = 0;
	}
	else
	{
		result.y = atan2(-data_[2], data_[0]);
		result.x = atan2(-data_[9], data_[5]);
		result.z = asin(data_[1]);
	}

	return result;
}



re::Vec3d re::Matrix4::getCenter() const
{
	return Vec3d(data_[12], data_[13], data_[14]);
}



re::Vec3d re::Matrix4::xAxis() const
{
	return Vec3d(data_[0], data_[1], data_[2]);
}



re::Vec3d re::Matrix4::yAxis() const
{
	return Vec3d(data_[4], data_[5], data_[6]);
}



re::Vec3d re::Matrix4::zAxis() const
{
	return Vec3d(data_[8], data_[9], data_[10]);
}



void re::Matrix4::inverse()
{
	float result[16];

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			result[j * 4 + i] = data_[i * 4 + j];

	// Position inversion is not tested!!!
	result[12] = data_[12] * (data_[5] * data_[10] - data_[9] * data_[6]) -
		data_[13] * (data_[4] * data_[10] - data_[8] * data_[6]) +
		data_[14] * (data_[4] * data_[9] - data_[8] * data_[5]);

	result[13] = data_[12] * (data_[1] * data_[10] - data_[9] * data_[2]) -
		data_[13] * (data_[0] * data_[10] - data_[8] * data_[2]) +
		data_[14] * (data_[0] * data_[9] - data_[8] * data_[1]);

	result[14] = data_[12] * (data_[1] * data_[6] - data_[5] * data_[2]) -
		data_[13] * (data_[0] * data_[6] - data_[4] * data_[2]) +
		data_[14] * (data_[0] * data_[5] - data_[4] * data_[1]);

	result[3] = result[7] = result[11] = 0;
	result[15] = 1.0f;

	set(result);
}



void re::Matrix4::transpose()
{
	float result[16];

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			result[j * 4 + i] = data_[i * 4 + j];

	set(result);
}



re::Matrix4 re::Matrix4::toInversed() const
{
	float result[16];

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			result[j * 4 + i] = data_[i * 4 + j];

	// Position inversion is not tested!!!
	result[12] = data_[12] * (data_[5] * data_[10] - data_[9] * data_[6]) -
		data_[13] * (data_[4] * data_[10] - data_[8] * data_[6]) +
		data_[14] * (data_[4] * data_[9] - data_[8] * data_[5]);

	result[13] = data_[12] * (data_[1] * data_[10] - data_[9] * data_[2]) -
		data_[13] * (data_[0] * data_[10] - data_[8] * data_[2]) +
		data_[14] * (data_[0] * data_[9] - data_[8] * data_[1]);

	result[14] = data_[12] * (data_[1] * data_[6] - data_[5] * data_[2]) -
		data_[13] * (data_[0] * data_[6] - data_[4] * data_[2]) +
		data_[14] * (data_[0] * data_[5] - data_[4] * data_[1]);

	result[3] = result[7] = result[11] = 0;
	result[15] = 1.0f;

	return Matrix4(result);
}



re::Matrix4 re::Matrix4::toTransposed() const
{
	float result[16];

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			result[j * 4 + i] = data_[i * 4 + j];
		}

	return Matrix4(result);
}



void re::Matrix4::rotate(float& x, float& y, float& z) const
{
	const float tx = x * data_[0] + y * data_[4] + z * data_[8];	// 0-0, 1-0, 2-0
	const float ty = x * data_[1] + y * data_[5] + z * data_[9];	// 0-1, 1-1, 2-1
	const float tz = x * data_[2] + y * data_[6] + z * data_[10];	// 0-2, 1-2, 2-2
	x = tx;
	y = ty;
	z = tz;
}



void re::Matrix4::rotate(float* vector) const
{
	rotate(vector[0], vector[1], vector[2]);
}



void re::Matrix4::rotate(Vec3d& vector) const
{
	rotate(vector.x, vector.y, vector.z);
}



void re::Matrix4::inverseRotate(float& x, float& y, float& z) const
{
	const float tx = x * data_[0] + y * data_[1] + z * data_[2];	// 0-0, 0-1, 0-2
	const float ty = x * data_[4] + y * data_[5] + z * data_[6];	// 1-0, 1-1, 1-2
	const float tz = x * data_[8] + y * data_[9] + z * data_[10];	// 2-0, 2-1, 2-2
	x = tx;
	y = ty;
	z = tz;
}



void re::Matrix4::inverseRotate(float* vector) const
{
	inverseRotate(vector[0], vector[1], vector[2]);
}



void re::Matrix4::inverseRotate(Vec3d& vector) const
{
	inverseRotate(vector.x, vector.y, vector.z);
}



void re::Matrix4::translate(float& x, float& y, float& z) const
{
	x += data_[12];	// 3-0
	y += data_[13];	// 3-1
	z += data_[14];	// 3-2
}



void re::Matrix4::translate(float* vector) const
{
	translate(vector[0], vector[1], vector[2]);
}



void re::Matrix4::translate(Vec3d& vector) const
{
	translate(vector.x, vector.y, vector.z);
}



void re::Matrix4::inverseTranslate(float& x, float& y, float& z) const
{
	x -= data_[12];	// 3-0
	y -= data_[13];	// 3-1
	z -= data_[14];	// 3-2
}



void re::Matrix4::inverseTranslate(float* vector) const
{
	inverseTranslate(vector[0], vector[1], vector[2]);
}



void re::Matrix4::inverseTranslate(Vec3d& vector) const
{
	inverseTranslate(vector.x, vector.y, vector.z);
}



void re::Matrix4::scale(float& x, float& y, float& z) const
{
	x *= data_[0];
	y *= data_[5];
	z *= data_[10];
}



void re::Matrix4::scale(float* vector) const
{
	scale(vector[0], vector[1], vector[2]);
}



void re::Matrix4::scale(Vec3d& vector) const
{
	scale(vector.x, vector.y, vector.z);
}



void re::Matrix4::inverseScale(float& x, float& y, float& z) const
{
	x /= data_[0];
	y /= data_[5];
	z /= data_[10];
}



void re::Matrix4::inverseScale(float* vector) const
{
	inverseScale(vector[0], vector[1], vector[2]);
}



void re::Matrix4::inverseScale(Vec3d& vector) const
{
	inverseScale(vector.x, vector.y, vector.z);
}

re::Matrix3 re::Matrix4::rotationMatrix() const
{
	Matrix3 result;
	memcpy(&result[0], &data_[0], sizeof(float) * 3);
	memcpy(&result[3], &data_[4], sizeof(float) * 3);
	memcpy(&result[6], &data_[8], sizeof(float) * 3);
	return result;
}



bool re::Matrix4::operator == (const Matrix4& matrix) const
{
	return !memcmp(data_, matrix.data_, sizeof(float) * 16);
}



bool re::Matrix4::operator != (const Matrix4& matrix) const
{
	return memcmp(data_, matrix.data_, sizeof(float) * 16) != 0;
}



re::Matrix4& re::Matrix4::operator = (const Matrix4& matrix)
{
	if (&matrix != this)
		memcpy(data_, matrix.data_, sizeof(float) * 16);

	return *this;
}



re::Matrix4 re::Matrix4::operator * (const Matrix4& matrix) const
{
	Matrix4 result(this);
	result *= matrix;
	return result;
}

re::Quaternion re::Matrix4::operator * (const Quaternion & q) const
{
	Quaternion result;
	result.x = data_[0] * q.x + data_[4] * q.y + data_[8]  * q.z + data_[12] * q.w;
	result.y = data_[1] * q.x + data_[5] * q.y + data_[9]  * q.z + data_[13] * q.w;
	result.z = data_[2] * q.x + data_[6] * q.y + data_[10] * q.z + data_[14] * q.w;
	result.w = data_[3] * q.x + data_[7] * q.y + data_[11] * q.z + data_[15] * q.w;
	return result;
}



void re::Matrix4::operator *= (const Matrix4& matrix)
{
	float result[16];
	const float* m1 = data_;
	const float* m2 = matrix.data_;

	result[0] = m1[0] * m2[0] + m1[4] * m2[1] + m1[8] * m2[2];
	result[1] = m1[1] * m2[0] + m1[5] * m2[1] + m1[9] * m2[2];
	result[2] = m1[2] * m2[0] + m1[6] * m2[1] + m1[10] * m2[2];
	result[3] = m1[3] * m2[0] + m1[7] * m2[1] + m1[11] * m2[2];

	result[4] = m1[0] * m2[4] + m1[4] * m2[5] + m1[8] * m2[6];
	result[5] = m1[1] * m2[4] + m1[5] * m2[5] + m1[9] * m2[6];
	result[6] = m1[2] * m2[4] + m1[6] * m2[5] + m1[10] * m2[6];
	result[7] = m1[3] * m2[4] + m1[7] * m2[5] + m1[11] * m2[6];

	result[8] = m1[0] * m2[8] + m1[4] * m2[9] + m1[8] * m2[10];
	result[9] = m1[1] * m2[8] + m1[5] * m2[9] + m1[9] * m2[10];
	result[10] = m1[2] * m2[8] + m1[6] * m2[9] + m1[10] * m2[10];
	result[11] = m1[3] * m2[8] + m1[7] * m2[9] + m1[11] * m2[10];

	result[12] = m1[0] * m2[12] + m1[4] * m2[13] + m1[8] * m2[14] + m1[12];
	result[13] = m1[1] * m2[12] + m1[5] * m2[13] + m1[9] * m2[14] + m1[13];
	result[14] = m1[2] * m2[12] + m1[6] * m2[13] + m1[10] * m2[14] + m1[14];
	result[15] = m1[3] * m2[12] + m1[7] * m2[13] + m1[11] * m2[14] + m1[15];

	set(result);
}



re::Matrix4::operator float* ()
{
	return data_;
}



re::Matrix4::operator const float* () const
{
	return data_;
}

float & re::Matrix4::operator[](size_t index)
{
	return data_[index];
}

const float & re::Matrix4::operator[](size_t index) const
{
	return data_[index];
}
