//////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:        reQuaternion.cpp
// Project:     reMath
// Description: Implementation of Quaternion class
// Copyright:   Copyright © 2004++ REGLabs
// Author:      Pavel Chikul
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "reMath/reQuaternion.h"
#include "reMath/reVec3d.h"
#include "reMath/reMatrix4.h"
#include <cstring>
#include <cmath>

re::Quaternion::Quaternion()
{
	set(0, 0, 0, 1);
}


re::Quaternion::Quaternion(const Quaternion& quaternion)
{
	set(quaternion);
}


re::Quaternion::Quaternion(const Quaternion* quaternion)
{
	set(quaternion->d);
}


re::Quaternion::Quaternion(float xValue, float yValue, float zValue, float wValue)
{
	set(xValue, yValue, zValue, wValue);
}


re::Quaternion::Quaternion(const float* quaternion)
{
	set(quaternion);
}


void re::Quaternion::set(const Quaternion& quaternion)
{
	memcpy(&d, quaternion.d, sizeof(d));
}


void re::Quaternion::set(float xValue, float yValue, float zValue, float wValue)
{
	x = xValue;
	y = yValue;
	z = zValue;
	w = wValue;
}


void re::Quaternion::set(const float* quaternion)
{
	memcpy(&d, quaternion, sizeof(d));
}


void re::Quaternion::set(float xValue, float yValue, float zValue)
{
	x = xValue;
	y = yValue;
	z = zValue;
	computeW();
}


void re::Quaternion::set(const Vec3d& vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
	computeW();
}


re::Quaternion re::Quaternion::fromEulers(Vec3d& vector)
{
	const float sinYaw = sinf(vector.z / 2.f);
	const float sinPitch = sinf(vector.y / 2.f);
	const float sinRoll = sinf(vector.x / 2.f);
	const float cosYaw = cosf(vector.z / 2.f);
	const float cosPitch = cosf(vector.y / 2.f);
	const float cosRoll = cosf(vector.x / 2.f);

	return Quaternion(
		sinRoll * cosPitch * cosYaw - cosRoll * sinPitch * sinYaw,
		cosRoll * sinPitch * cosYaw + sinRoll * cosPitch * sinYaw,
		cosRoll * cosPitch * sinYaw - sinRoll * sinPitch * cosYaw,
		cosRoll * cosPitch * cosYaw + sinRoll * sinPitch * sinYaw
		);
}


re::Quaternion re::Quaternion::fromEulerXRotation(float angle)
{
	const float halfAngle = angle * 0.5f;
	return Quaternion(sinf(halfAngle), 0, 0, cosf(halfAngle));
}


re::Quaternion re::Quaternion::fromEulerYRotation(float angle)
{
	const float halfAngle = angle * 0.5f;
	return Quaternion(0, sinf(halfAngle), 0, cosf(halfAngle));
}


re::Quaternion re::Quaternion::fromEulerZRotation(float angle)
{
	const float halfAngle = angle * 0.5f;
	return Quaternion(0, 0, sinf(halfAngle), cosf(halfAngle));
}


void re::Quaternion::computeW()
{
	if (!x && !y && !z)
	{
		w = 1.f;
	}
	else
	{
		const float temp = 1.0f - (x*x + y*y + z*z);
		w = temp < 0 ? 0 : -sqrtf(temp);
	}
}


re::Vec3d re::Quaternion::getEulers() const
{
	// This equation works rihgt too
	/*Result.x = atan2f(2*(w*x + y*z), (w*w - x*x - y*y + z*z));
	Result.y = asinf(-2*(x*z - w*y));
	Result.z = atan2f(2*(w*z + x*y), (w*w + x*x - y*y + z*z));*/

	/*return Vec3d(
	atan2f(2*(w*x + y*z), 1-2*(x*x + y*y)),
	asinf(2*(w*y - z*x)),
	atan2f(2*(w*z + x*y), 1-2*(y*y + z*z)));*/

	const float m11 = w*w + x*x - y*y - z*z;
	const float m21 = 2 * (x * y + z * w);
	float m31 = 2 * (z * x - y * w);
	const float m32 = 2 * (z * y + x * w);
	const float m33 = w*w - x*x - y*y + z*z;

	// Range validity check
	if (m31 < -1.f) m31 = -1.f;
	if (m31 > 1.f)	m31 = 1.f;

	return Vec3d(atan2f(m32, m33), asinf(-m31), atan2f(m21, m11));
}


re::Matrix4 re::Quaternion::getMatrix() const
{
	float x2, xx, xy, xz, xw, y2, yy, yz, yw, z2, zz, zw;

	x2 = x + x;		y2 = y + y;		z2 = z + z;
	xx = x * x2;	yy = y * y2;	zz = z * z2;
	xy = x * y2;	yz = y * z2;	zw = w * z2;
	xz = x * z2;	yw = w * y2;
	xw = w * x2;

	Matrix4 result;

	result[0] = 1.0f - (yy + zz);	// Row 1
	result[1] = xy + zw;
	result[2] = xz - yw;
	result[3] = 0;

	result[4] = xy - zw;			// Row 2
	result[5] = 1.0f - (xx + zz);
	result[6] = yz + xw;
	result[7] = 0;

	result[8] = xz + yw;			// Row 3
	result[9] = yz - xw;
	result[10] = 1.0f - (xx + yy);
	result[11] = 0;

	result[12] = 0;				// Row 4
	result[13] = 0;
	result[14] = 0;
	result[15] = 1;

	return result;
}


float re::Quaternion::length() const
{
	return sqrtf(x*x + y*y + z*z + w*w);
}


void re::Quaternion::normalize()
{
	const float d = length();

	if (d)
	{
		x /= d;
		y /= d;
		z /= d;
		w /= d;
	}
	else
	{
		set(0, 0, 0, 1);
	}
}


void re::Quaternion::negate()
{
	x = -x;
	y = -y;
	z = -z;
	w = -w;
}


re::Quaternion re::Quaternion::slerp(const Quaternion& quaternion, float scale) const
{
	Quaternion first(this);
	Quaternion second(quaternion);
	float dot = first.dot(second);

	if (dot < 0.0f)
	{
		second.negate();
		dot = -dot;
	}

	// Range validity check
	if (dot < -1.f) dot = -1.f;
	if (dot > 1.f) dot = 1.f;

	if ((1.f - dot) > 0.00001f) // If dot > 0.99999 && dot < 1.00001 - do SLERP
	{
		const float angle = acosf(dot); // Calculate the angle between the quaternions
		Quaternion result((first * sinf(angle * (1.f - scale)) + second * sinf(angle * scale)) / sinf(angle));
		result.normalize();
		return result;
	}
	else // Otherwise - do LERP
	{
		return first.lerp(second, scale);
	}
}


re::Quaternion re::Quaternion::lerp(const Quaternion& quaternion, float scale) const
{
	Quaternion result(Quaternion(this) + ((quaternion - Quaternion(this)) * scale));
	result.normalize();
	return result;
}


float re::Quaternion::dot(const Quaternion& quaternion) const
{
	return (x * quaternion.x + y * quaternion.y + z * quaternion.z + w * quaternion.w);
}


bool re::Quaternion::operator == (const Quaternion& quaternion) const
{
	return (x == quaternion.x && y == quaternion.y && z == quaternion.z && w == quaternion.w);
}


bool re::Quaternion::operator != (const Quaternion& quaternion) const
{
	return (x != quaternion.x || y != quaternion.y || z != quaternion.z || w != quaternion.w);
}


re::Quaternion& re::Quaternion::operator = (const Quaternion& quaternion)
{
	if (&quaternion != this)
		memcpy(d, quaternion.d, sizeof(d));

	return *this;
}


re::Quaternion re::Quaternion::operator - () const
{
	Quaternion result(this);
	result.negate();
	return result;
}


re::Quaternion re::Quaternion::operator + (const Quaternion& quaternion) const
{
	return Quaternion(x + quaternion.x, y + quaternion.y, z + quaternion.z, w + quaternion.w);
}


re::Quaternion re::Quaternion::operator - (const Quaternion& quaternion) const
{
	return Quaternion(x - quaternion.x, y - quaternion.y, z - quaternion.z, w - quaternion.w);
}


re::Quaternion re::Quaternion::operator * (const Quaternion& quaternion) const
{
	const float xComponent = w * quaternion.x + quaternion.w * x + (y * quaternion.z - z * quaternion.y);
	const float yComponent = w * quaternion.y + quaternion.w * y + (z * quaternion.x - x * quaternion.z);
	const float zComponent = w * quaternion.z + quaternion.w * z + (x * quaternion.y - y * quaternion.x);
	const float wComponent = w * quaternion.w - (x * quaternion.x + y * quaternion.y + z * quaternion.z);
	return Quaternion(xComponent, yComponent, zComponent, wComponent);
}


re::Quaternion re::operator * (float value, const re::Quaternion& quaternion)
{
	return re::Quaternion(quaternion.x * value, quaternion.y * value, quaternion.z * value, quaternion.w * value);
}


re::Quaternion re::operator * (const re::Quaternion& quaternion, float value)
{
	return re::Quaternion(quaternion.x * value, quaternion.y * value, quaternion.z * value, quaternion.w * value);
}


re::Quaternion re::Quaternion::operator / (float value) const
{
	return Quaternion(x / value, y / value, z / value, w / value);
}


re::Quaternion& re::Quaternion::operator += (const Quaternion& quaternion)
{
	x += quaternion.x;
	y += quaternion.y;
	z += quaternion.z;
	w += quaternion.w;

	return *this;
}


re::Quaternion& re::Quaternion::operator -= (const Quaternion& quaternion)
{
	x -= quaternion.x;
	y -= quaternion.y;
	z -= quaternion.z;
	w -= quaternion.w;

	return *this;
}


re::Quaternion& re::Quaternion::operator *= (const Quaternion& quaternion)
{
	const float xComponent = w * quaternion.x + quaternion.w * x + (y * quaternion.z - z * quaternion.y);
	const float yComponent = w * quaternion.y + quaternion.w * y + (z * quaternion.x - x * quaternion.z);
	const float zComponent = w * quaternion.z + quaternion.w * z + (x * quaternion.y - y * quaternion.x);
	const float wComponent = w * quaternion.w - (x * quaternion.x + y * quaternion.y + z * quaternion.z);
	set(xComponent, yComponent, zComponent, wComponent);

	return *this;
}


re::Quaternion& re::Quaternion::operator *= (float value)
{
	x *= value;
	y *= value;
	z *= value;
	w *= value;

	return *this;
}


re::Quaternion& re::Quaternion::operator /= (float value)
{
	x /= value;
	y /= value;
	z /= value;
	w /= value;

	return *this;
}


re::Quaternion::operator float* ()
{
	return d;
}


re::Quaternion::operator const float* () const
{
	return d;
}


float & re::Quaternion::operator[](size_t index)
{
	return d[index];
}


const float & re::Quaternion::operator[](size_t index) const
{
	return d[index];
}
