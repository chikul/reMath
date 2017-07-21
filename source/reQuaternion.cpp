//////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:		reQuaternion.cpp
// Project:		Razor Edge Classes
// Description:	Implementation of Quaternion class (Math Module)
// Copyright:	Copyright © 2004++ REGLabs
// Author:		Pavel Chikul
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "reQuaternion.h"
#include "reVec3d.h"
#include "reMatrix.h"
#include <string.h>
#include <math.h>

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
	float sinYaw = sinf(vector.z / 2.f);
	float sinPitch = sinf(vector.y / 2.f);
	float sinRoll = sinf(vector.x / 2.f);
	float cosYaw = cosf(vector.z / 2.f);
	float cosPitch = cosf(vector.y / 2.f);
	float cosRoll = cosf(vector.x / 2.f);

	return Quaternion(
		sinRoll * cosPitch * cosYaw - cosRoll * sinPitch * sinYaw,
		cosRoll * sinPitch * cosYaw + sinRoll * cosPitch * sinYaw,
		cosRoll * cosPitch * sinYaw - sinRoll * sinPitch * cosYaw,
		cosRoll * cosPitch * cosYaw + sinRoll * sinPitch * sinYaw
		);
}



re::Quaternion re::Quaternion::fromEulerXRotation(float angle)
{
	float halfAngle = angle * 0.5f;
	return Quaternion(sinf(halfAngle), 0, 0, cosf(halfAngle));
}



re::Quaternion re::Quaternion::fromEulerYRotation(float angle)
{
	float halfAngle = angle * 0.5f;
	return Quaternion(0, sinf(halfAngle), 0, cosf(halfAngle));
}



re::Quaternion re::Quaternion::fromEulerZRotation(float angle)
{
	float halfAngle = angle * 0.5f;
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
		float temp = 1.0f - (x*x + y*y + z*z);
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

	float m11 = w*w + x*x - y*y - z*z;
	float m21 = 2 * (x * y + z * w);
	float m31 = 2 * (z * x - y * w);
	float m32 = 2 * (z * y + x * w);
	float m33 = w*w - x*x - y*y + z*z;

	// Range validity check
	if (m31 < -1.f) m31 = -1.f;
	if (m31 > 1.f)	m31 = 1.f;

	return Vec3d(atan2f(m32, m33), asinf(-m31), atan2f(m21, m11));
}



re::Matrix re::Quaternion::getMatrix() const
{
	float x2, xx, xy, xz, xw, y2, yy, yz, yw, z2, zz, zw;

	x2 = x + x;		y2 = y + y;		z2 = z + z;
	xx = x * x2;	yy = y * y2;	zz = z * z2;
	xy = x * y2;	yz = y * z2;	zw = w * z2;
	xz = x * z2;	yw = w * y2;
	xw = w * x2;

	Matrix result;
	float* data = result;

	data[0] = 1.0f - (yy + zz);	// Row 1
	data[1] = xy + zw;
	data[2] = xz - yw;
	data[3] = 0;

	data[4] = xy - zw;			// Row 2
	data[5] = 1.0f - (xx + zz);
	data[6] = yz + xw;
	data[7] = 0;

	data[8] = xz + yw;			// Row 3
	data[9] = yz - xw;
	data[10] = 1.0f - (xx + yy);
	data[11] = 0;

	data[12] = 0;				// Row 4
	data[13] = 0;
	data[14] = 0;
	data[15] = 1;

	return result;
}



float re::Quaternion::length() const
{
	return sqrtf(x*x + y*y + z*z + w*w);
}



void re::Quaternion::normalize()
{
	float d = length();

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
		float angle = acosf(dot); // Calculate the angle between the quaternions
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
	Quaternion result(Quaternion(this) + ((quaternion - this) * scale));
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
	float xComponent = w * quaternion.x + quaternion.w * x + (y * quaternion.z - z * quaternion.y);
	float yComponent = w * quaternion.y + quaternion.w * y + (z * quaternion.x - x * quaternion.z);
	float zComponent = w * quaternion.z + quaternion.w * z + (x * quaternion.y - y * quaternion.x);
	float wComponent = w * quaternion.w - (x * quaternion.x + y * quaternion.y + z * quaternion.z);
	return Quaternion(xComponent, yComponent, zComponent, wComponent);
}



re::Quaternion operator * (float value, const re::Quaternion& quaternion)
{
	return re::Quaternion(quaternion.x * value, quaternion.y * value, quaternion.z * value, quaternion.w * value);
}



re::Quaternion operator * (const re::Quaternion& quaternion, float value)
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
	float xComponent = w * quaternion.x + quaternion.w * x + (y * quaternion.z - z * quaternion.y);
	float yComponent = w * quaternion.y + quaternion.w * y + (z * quaternion.x - x * quaternion.z);
	float zComponent = w * quaternion.z + quaternion.w * z + (x * quaternion.y - y * quaternion.x);
	float wComponent = w * quaternion.w - (x * quaternion.x + y * quaternion.y + z * quaternion.z);
	set(xComponent, yComponent, zComponent, wComponent);

	return *this;
}



re::Quaternion& re::Quaternion::operator *= (float f)
{
	x *= f;
	y *= f;
	z *= f;
	w *= f;

	return *this;
}



re::Quaternion& re::Quaternion::operator /= (float f)
{
	x /= f;
	y /= f;
	z /= f;
	w /= f;

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
