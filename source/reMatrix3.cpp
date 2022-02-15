//////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:        reMatrix4.cpp
// Project:     reMath
// Description: Implementation of Matrix3 class (Math Module)
// Copyright:   Copyright © 2004++ REGLabs
// Author:      Pavel Chikul
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "reMatrix3.h"
#include "reVec3d.h"
#include "reMatrix4.h"
#include <cstring>
#include <cmath>
#include "reMathUtil.h"

re::Matrix3::Matrix3()
{
	loadIdentity();
}

re::Matrix3::Matrix3(const Matrix3 & matrix)
{
	if (&matrix == this)
		return;

	memcpy(data_, matrix.data_, sizeof(float) * 9);
}

re::Matrix3::Matrix3(const Matrix3 * matrix)
{
	if (matrix == this || !matrix)
		return;

	memcpy(data_, matrix->data_, sizeof(float) * 9);
}

re::Matrix3::Matrix3(const float * matrix)
{
	if (!matrix)
	{
		loadIdentity();
		return;
	}

	memcpy(data_, matrix, sizeof(float) * 9);
}

re::Matrix3::Matrix3(const Matrix4& matrix)
{
	memcpy(&data_[0], &matrix[0], sizeof(float) * 3);
	memcpy(&data_[3], &matrix[4], sizeof(float) * 3);
	memcpy(&data_[6], &matrix[8], sizeof(float) * 3);
}

void re::Matrix3::loadIdentity()
{
	memset(data_, 0, sizeof(float) * 9);
	data_[0] = data_[4] = data_[8] = 1;
}

void re::Matrix3::set(const float * matrix)
{
	if (!matrix)
	{
		loadIdentity();
		return;
	}

	memcpy(data_, matrix, sizeof(float) * 9);
}

void re::Matrix3::setRotation(float x, float y, float z)
{
	const float cx = cos(x);				//	| 0  1  2 |		|0-0  0-1  0-2|
	const float sx = sin(x);				//	| 3  4  5 |		|1-0  1-1  1-2|
	const float cy = cos(y);				//	| 6  7  8 |		|2-0  2-1  2-2|
	const float sy = sin(y);
	const float cz = cos(z);
	const float sz = sin(z);
	const float sxsy = sx * sy;
	const float cxsy = cx * sy;

	data_[0] = cy * cz;						/* 0-0 \                      */
	data_[1] = cy * sz;						/* 0-1	|- top row, 1-3 col.  */
	data_[2] = -sy;							/* 0-2 /                      */

	data_[3] = sxsy * cz - cx * sz;			/* 1-0 \                      */
	data_[4] = sxsy * sz + cx * cz;			/* 1-1  |- 2-nd row, 1-3 col. */
	data_[5] = sx * cy;						/* 1-2 /                      */

	data_[6] = cxsy * cz + sx * sz;			/* 2-0 \                      */
	data_[7] = cxsy * sz - sx * cz;			/* 2-1  |- 3-rd row, 1-3 col. */
	data_[8] = cx * cy;						/* 2-2 /                      */
}

void re::Matrix3::setRotation(const float * r)
{
	setRotation(r[0], r[1], r[2]);
}

void re::Matrix3::setRotation(const Vec3d & r)
{
	setRotation(r.x, r.y, r.z);
}

re::Vec3d re::Matrix3::getEulers() const
{
	Vec3d result;

	if (data_[1] > 0.9998) // singularity at north pole
	{
		result.y = atan2(data_[6], data_[8]);
		result.z = PI / 2;
		result.x = 0;
	}
	else if (data_[1] < -0.9998) // singularity at south pole
	{
		result.y = atan2(data_[6], data_[8]);
		result.z = -PI / 2;
		result.x = 0;
	}
	else
	{
		result.y = atan2(-data_[2], data_[0]);
		result.x = atan2(-data_[7], data_[4]);
		result.z = asin(data_[1]);
	}

	return result;
}

void re::Matrix3::rotate(float & x, float & y, float & z) const
{
	const float tx = x * data_[0] + y * data_[3] + z * data_[6];	// 0-0, 1-0, 2-0
	const float ty = x * data_[1] + y * data_[4] + z * data_[7];	// 0-1, 1-1, 2-1
	const float tz = x * data_[2] + y * data_[5] + z * data_[8];	// 0-2, 1-2, 2-2
	x = tx;
	y = ty;
	z = tz;
}

void re::Matrix3::rotate(float * vector) const
{
	rotate(vector[0], vector[1], vector[2]);
}

void re::Matrix3::rotate(Vec3d & vector) const
{
	rotate(vector.x, vector.y, vector.z);
}

void re::Matrix3::inverseRotate(float & x, float & y, float & z) const
{
	const float tx = x * data_[0] + y * data_[1] + z * data_[2];	// 0-0, 0-1, 0-2
	const float ty = x * data_[3] + y * data_[4] + z * data_[5];	// 1-0, 1-1, 1-2
	const float tz = x * data_[6] + y * data_[7] + z * data_[8];	// 2-0, 2-1, 2-2
	x = tx;
	y = ty;
	z = tz;
}

void re::Matrix3::inverseRotate(float * vector) const
{
	inverseRotate(vector[0], vector[1], vector[2]);
}

void re::Matrix3::inverseRotate(Vec3d & vector) const
{
	inverseRotate(vector.x, vector.y, vector.z);
}

bool re::Matrix3::operator == (const Matrix3 & matrix) const
{
	return !memcmp(data_, matrix.data_, sizeof(float) * 9);
}

bool re::Matrix3::operator != (const Matrix3 & matrix) const
{
	return memcmp(data_, matrix.data_, sizeof(float) * 9) != 0;
}

re::Matrix3 & re::Matrix3::operator = (const Matrix3 & matrix)
{
	if (&matrix != this)
		memcpy(data_, matrix.data_, sizeof(float) * 9);

	return *this;
}

re::Matrix3::operator float * ()
{
	return data_;
}

re::Matrix3::operator const float * () const
{
	return data_;
}

float & re::Matrix3::operator[](size_t index)
{
	return data_[index];
}

const float & re::Matrix3::operator[](size_t index) const
{
	return data_[index];
}
