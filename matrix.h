#pragma once

#include <math.h>

#include "vector.h"

#define DegToRad(x) ((x) * 3.1415926536f / 180.0f)

struct mat3;
struct mat4;

/********************************************************************************/
/*								mat3											*/
/********************************************************************************/

struct mat3
{
	mat3()
	{
		mat[0] = 1.0; mat[3] = 0.0; mat[6] = 0.0;
		mat[1] = 0.0; mat[4] = 1.0; mat[7] = 0.0;
		mat[2] = 0.0; mat[5] = 0.0; mat[8] = 1.0;
	}

	explicit mat3(const float* m)
	{
		mat[0] = m[0]; mat[3] = m[3]; mat[6] = m[6];
		mat[1] = m[1]; mat[4] = m[4]; mat[7] = m[7];
		mat[2] = m[2]; mat[5] = m[5]; mat[8] = m[8];
	}

	mat3(const mat3& m)
	{
		mat[0] = m.mat[0]; mat[3] = m.mat[3]; mat[6] = m.mat[6];
		mat[1] = m.mat[1]; mat[4] = m.mat[4]; mat[7] = m.mat[7];
		mat[2] = m.mat[2]; mat[5] = m.mat[5]; mat[8] = m.mat[8];
	}

	mat3(const vec3& row1, const vec3& row2, const vec3& row3)
	{
		mat[0] = row1.x; mat[3] = row2.x; mat[6] = row3.x;
		mat[1] = row1.y; mat[4] = row2.y; mat[7] = row3.y;
		mat[2] = row1.z; mat[5] = row2.z; mat[8] = row3.z;
	}

	explicit mat3(const mat4& m);

	// Binary operators
	vec3 operator*(const vec3& v) const
	{
		vec3 ret;
		ret.x = mat[0] * v.x + mat[3] * v.y + mat[6] * v.z;
		ret.y = mat[1] * v.x + mat[4] * v.y + mat[7] * v.z;
		ret.z = mat[2] * v.x + mat[5] * v.y + mat[8] * v.z;
		return ret;
	}

	vec4 operator*(const vec4& v) const
	{
		vec4 ret;
		ret.x = mat[0] * v.x + mat[3] * v.y + mat[6] * v.z;
		ret.y = mat[1] * v.x + mat[4] * v.y + mat[7] * v.z;
		ret.z = mat[2] * v.x + mat[5] * v.y + mat[8] * v.z;
		ret.w = v.w;
		return ret;
	}

	mat3 operator*(float f) const
	{
		mat3 ret;
		ret.mat[0] = mat[0] * f; ret.mat[3] = mat[3] * f; ret.mat[6] = mat[6] * f;
		ret.mat[1] = mat[1] * f; ret.mat[4] = mat[4] * f; ret.mat[7] = mat[7] * f;
		ret.mat[2] = mat[2] * f; ret.mat[5] = mat[5] * f; ret.mat[8] = mat[8] * f;
		return ret;
	}

	mat3 operator*(const mat3& m) const
	{
		mat3 ret;
		ret.mat[0] = mat[0] * m.mat[0] + mat[3] * m.mat[1] + mat[6] * m.mat[2];
		ret.mat[1] = mat[1] * m.mat[0] + mat[4] * m.mat[1] + mat[7] * m.mat[2];
		ret.mat[2] = mat[2] * m.mat[0] + mat[5] * m.mat[1] + mat[8] * m.mat[2];
		ret.mat[3] = mat[0] * m.mat[3] + mat[3] * m.mat[4] + mat[6] * m.mat[5];
		ret.mat[4] = mat[1] * m.mat[3] + mat[4] * m.mat[4] + mat[7] * m.mat[5];
		ret.mat[5] = mat[2] * m.mat[3] + mat[5] * m.mat[4] + mat[8] * m.mat[5];
		ret.mat[6] = mat[0] * m.mat[6] + mat[3] * m.mat[7] + mat[6] * m.mat[8];
		ret.mat[7] = mat[1] * m.mat[6] + mat[4] * m.mat[7] + mat[7] * m.mat[8];
		ret.mat[8] = mat[2] * m.mat[6] + mat[5] * m.mat[7] + mat[8] * m.mat[8];
		return ret;
	}

	mat3 operator+(const mat3& m) const
	{
		mat3 ret;
		ret.mat[0] = mat[0] + m.mat[0]; ret.mat[3] = mat[3] + m.mat[3]; ret.mat[6] = mat[6] + m.mat[6];
		ret.mat[1] = mat[1] + m.mat[1]; ret.mat[4] = mat[4] + m.mat[4]; ret.mat[7] = mat[7] + m.mat[7];
		ret.mat[2] = mat[2] + m.mat[2]; ret.mat[5] = mat[5] + m.mat[5]; ret.mat[8] = mat[8] + m.mat[8];
		return ret;
	}

	mat3 operator-(const mat3& m) const
	{
		mat3 ret;
		ret.mat[0] = mat[0] - m.mat[0]; ret.mat[3] = mat[3] - m.mat[3]; ret.mat[6] = mat[6] - m.mat[6];
		ret.mat[1] = mat[1] - m.mat[1]; ret.mat[4] = mat[4] - m.mat[4]; ret.mat[7] = mat[7] - m.mat[7];
		ret.mat[2] = mat[2] - m.mat[2]; ret.mat[5] = mat[5] - m.mat[5]; ret.mat[8] = mat[8] - m.mat[8];
		return ret;
	}

	// Assignment operators
	mat3& operator*=(float f)
	{
		return *this = *this * f;
	}

	mat3& operator*=(const mat3& m)
	{
		return *this = *this * m;
	}

	mat3& operator+=(const mat3& m)
	{
		return *this = *this + m;
	}

	mat3& operator-=(const mat3& m)
	{
		return *this = *this - m;
	}

	// Functions
	mat3 transpose() const
	{
		mat3 ret;
		ret.mat[0] = mat[0]; ret.mat[3] = mat[1]; ret.mat[6] = mat[2];
		ret.mat[1] = mat[3]; ret.mat[4] = mat[4]; ret.mat[7] = mat[5];
		ret.mat[2] = mat[6]; ret.mat[5] = mat[7]; ret.mat[8] = mat[8];
		return ret;
	}

	float det() const
	{
		float det;
		det = mat[0] * mat[4] * mat[8];
		det += mat[3] * mat[7] * mat[2];
		det += mat[6] * mat[1] * mat[5];
		det -= mat[6] * mat[4] * mat[2];
		det -= mat[3] * mat[1] * mat[8];
		det -= mat[0] * mat[7] * mat[5];
		return det;
	}

	mat3 inverse() const
	{
		mat3 ret;

		float idet = 1.0f / det();

		ret.mat[0] = (mat[4] * mat[8] - mat[7] * mat[5]) * idet;
		ret.mat[1] = -(mat[1] * mat[8] - mat[7] * mat[2]) * idet;
		ret.mat[2] = (mat[1] * mat[5] - mat[4] * mat[2]) * idet;
		ret.mat[3] = -(mat[3] * mat[8] - mat[6] * mat[5]) * idet;
		ret.mat[4] = (mat[0] * mat[8] - mat[6] * mat[2]) * idet;
		ret.mat[5] = -(mat[0] * mat[5] - mat[3] * mat[2]) * idet;
		ret.mat[6] = (mat[3] * mat[7] - mat[6] * mat[4]) * idet;
		ret.mat[7] = -(mat[0] * mat[7] - mat[6] * mat[1]) * idet;
		ret.mat[8] = (mat[0] * mat[4] - mat[3] * mat[1]) * idet;

		return ret;
	}

	void zero()
	{
		mat[0] = 0.0; mat[3] = 0.0; mat[6] = 0.0;
		mat[1] = 0.0; mat[4] = 0.0; mat[7] = 0.0;
		mat[2] = 0.0; mat[5] = 0.0; mat[8] = 0.0;
	}

	void identity()
	{
		mat[0] = 1.0; mat[3] = 0.0; mat[6] = 0.0;
		mat[1] = 0.0; mat[4] = 1.0; mat[7] = 0.0;
		mat[2] = 0.0; mat[5] = 0.0; mat[8] = 1.0;
	}

	void rotate(const vec3& axis, float angle)
	{
		float rad = DegToRad(angle);
		float c = cosf(rad);
		float s = sinf(rad);

		vec3 v = axis;

		v.normalize();

		float xx = v.x * v.x;
		float yy = v.y * v.y;
		float zz = v.z * v.z;
		float xy = v.x * v.y;
		float yz = v.y * v.z;
		float zx = v.z * v.x;
		float xs = v.x * s;
		float ys = v.y * s;
		float zs = v.z * s;

		mat[0] = (1.0f - c) * xx + c; mat[3] = (1.0f - c) * xy - zs; mat[6] = (1.0f - c) * zx + ys;
		mat[1] = (1.0f - c) * xy + zs; mat[4] = (1.0f - c) * yy + c; mat[7] = (1.0f - c) * yz - xs;
		mat[2] = (1.0f - c) * zx - ys; mat[5] = (1.0f - c) * yz + xs; mat[8] = (1.0f - c) * zz + c;
	}

	void rotate_x(float angle)
	{
		float rad = DegToRad(angle);
		float c = cosf(rad);
		float s = sinf(rad);

		mat3 m;

		m.mat[0] = 1.0; m.mat[3] = 0.0; m.mat[6] = 0.0;
		m.mat[1] = 0.0; m.mat[4] = c; m.mat[7] = -s;
		m.mat[2] = 0.0; m.mat[5] = s; m.mat[8] = c;

		this->operator*=(m);
	}

	void rotate_y(float angle)
	{
		float rad = DegToRad(angle);
		float c = cosf(rad);
		float s = sinf(rad);

		mat3 m;

		m.mat[0] = c; m.mat[3] = 0.0; m.mat[6] = s;
		m.mat[1] = 0.0; m.mat[4] = 1.0; m.mat[7] = 0.0;
		m.mat[2] = -s; m.mat[5] = 0.0; m.mat[8] = c;

		this->operator*=(m);
	}

	void rotate_z(float angle)
	{
		float rad = DegToRad(angle);
		float c = cosf(rad);
		float s = sinf(rad);

		mat3 m;

		m.mat[0] = c; m.mat[3] = -s; m.mat[6] = 0.0;
		m.mat[1] = s; m.mat[4] = c; m.mat[7] = 0.0;
		m.mat[2] = 0.0; m.mat[5] = 0.0; m.mat[8] = 1.0;

		this->operator*=(m);
	}

	void scale(const vec3 &v)
	{
		mat3 m;

		m.mat[0] = v.x; m.mat[3] = 0.0; m.mat[6] = 0.0;
		m.mat[1] = 0.0; m.mat[4] = v.y; m.mat[7] = 0.0;
		m.mat[2] = 0.0; m.mat[5] = 0.0; m.mat[8] = v.z;

		this->operator*=(m);
	}

	void orthonormalize()
	{
		vec3 x(mat[0], mat[1], mat[2]);
		vec3 y(mat[3], mat[4], mat[5]);
		vec3 z;

		x.normalize();
		z.cross(x, y);
		z.normalize();
		y.cross(z, x);
		y.normalize();

		mat[0] = x.x; mat[3] = y.x; mat[6] = z.x;
		mat[1] = x.y; mat[4] = y.y; mat[7] = z.y;
		mat[2] = x.z; mat[5] = y.z; mat[8] = z.z;
	}

	float mat[9];
};

/********************************************************************************/
/*								mat4											*/
/********************************************************************************/

struct mat4
{
	mat4()
	{
		mat[0] = 1.0; mat[4] = 0.0; mat[8] = 0.0; mat[12] = 0.0;
		mat[1] = 0.0; mat[5] = 1.0; mat[9] = 0.0; mat[13] = 0.0;
		mat[2] = 0.0; mat[6] = 0.0; mat[10] = 1.0; mat[14] = 0.0;
		mat[3] = 0.0; mat[7] = 0.0; mat[11] = 0.0; mat[15] = 1.0;
	}

	mat4(const vec4& row1, const vec4& row2, const vec4& row3, const vec4& row4)
	{
		mat[0] = row1.x; mat[4] = row2.x; mat[8] = row3.x; mat[12] = row4.x;
		mat[1] = row1.y; mat[5] = row2.y; mat[9] = row3.y; mat[13] = row4.y;
		mat[2] = row1.z; mat[6] = row2.z; mat[10] = row3.z; mat[14] = row4.z;
		mat[3] = row1.w; mat[7] = row2.w; mat[11] = row3.w; mat[15] = row4.w;
	}

	explicit mat4(const mat3& m)
	{
		mat[0] = m.mat[0]; mat[4] = m.mat[3]; mat[8] = m.mat[6]; mat[12] = 0.0;
		mat[1] = m.mat[1]; mat[5] = m.mat[4]; mat[9] = m.mat[7]; mat[13] = 0.0;
		mat[2] = m.mat[2]; mat[6] = m.mat[5]; mat[10] = m.mat[8]; mat[14] = 0.0;
		mat[3] = 0.0;  mat[7] = 0.0;  mat[11] = 0.0;  mat[15] = 1.0;
	}

	explicit mat4(const float* m)
	{
		mat[0] = m[0]; mat[4] = m[4]; mat[8] = m[8]; mat[12] = m[12];
		mat[1] = m[1]; mat[5] = m[5]; mat[9] = m[9]; mat[13] = m[13];
		mat[2] = m[2]; mat[6] = m[6]; mat[10] = m[10]; mat[14] = m[14];
		mat[3] = m[3]; mat[7] = m[7]; mat[11] = m[11]; mat[15] = m[15];
	}

	mat4(const mat4& m)
	{
		mat[0] = m.mat[0]; mat[4] = m.mat[4]; mat[8] = m.mat[8]; mat[12] = m.mat[12];
		mat[1] = m.mat[1]; mat[5] = m.mat[5]; mat[9] = m.mat[9]; mat[13] = m.mat[13];
		mat[2] = m.mat[2]; mat[6] = m.mat[6]; mat[10] = m.mat[10]; mat[14] = m.mat[14];
		mat[3] = m.mat[3]; mat[7] = m.mat[7]; mat[11] = m.mat[11]; mat[15] = m.mat[15];
	}

	// Binary operators
	vec3 operator*(const vec3& v) const
	{
		vec3 ret;
		ret.x = mat[0] * v.x + mat[4] * v.y + mat[8] * v.z + mat[12];
		ret.y = mat[1] * v.x + mat[5] * v.y + mat[9] * v.z + mat[13];
		ret.z = mat[2] * v.x + mat[6] * v.y + mat[10] * v.z + mat[14];
		float w = mat[3] * v.x + mat[7] * v.y + mat[11] * v.z + mat[15];
		ret.x /= w; ret.y /= w; ret.z /= w;
		return ret;
	}

	vec4 operator*(const vec4& v) const
	{
		vec4 ret;
		ret.x = mat[0] * v.x + mat[4] * v.y + mat[8] * v.z + mat[12] * v.w;
		ret.y = mat[1] * v.x + mat[5] * v.y + mat[9] * v.z + mat[13] * v.w;
		ret.z = mat[2] * v.x + mat[6] * v.y + mat[10] * v.z + mat[14] * v.w;
		ret.w = mat[3] * v.x + mat[7] * v.y + mat[11] * v.z + mat[15] * v.w;
		return ret;
	}

	mat4 operator*(float f) const
	{
		mat4 ret;
		ret.mat[0] = mat[0] * f; ret.mat[4] = mat[4] * f; ret.mat[8] = mat[8] * f; ret.mat[12] = mat[12] * f;
		ret.mat[1] = mat[1] * f; ret.mat[5] = mat[5] * f; ret.mat[9] = mat[9] * f; ret.mat[13] = mat[13] * f;
		ret.mat[2] = mat[2] * f; ret.mat[6] = mat[6] * f; ret.mat[10] = mat[10] * f; ret.mat[14] = mat[14] * f;
		ret.mat[3] = mat[3] * f; ret.mat[7] = mat[7] * f; ret.mat[11] = mat[11] * f; ret.mat[15] = mat[15] * f;
		return ret;
	}

	mat4 operator*(const mat4 &m) const
	{
		mat4 ret;
		ret.mat[0] = mat[0] * m.mat[0] + mat[4] * m.mat[1] + mat[8] * m.mat[2] + mat[12] * m.mat[3];
		ret.mat[1] = mat[1] * m.mat[0] + mat[5] * m.mat[1] + mat[9] * m.mat[2] + mat[13] * m.mat[3];
		ret.mat[2] = mat[2] * m.mat[0] + mat[6] * m.mat[1] + mat[10] * m.mat[2] + mat[14] * m.mat[3];
		ret.mat[3] = mat[3] * m.mat[0] + mat[7] * m.mat[1] + mat[11] * m.mat[2] + mat[15] * m.mat[3];
		ret.mat[4] = mat[0] * m.mat[4] + mat[4] * m.mat[5] + mat[8] * m.mat[6] + mat[12] * m.mat[7];
		ret.mat[5] = mat[1] * m.mat[4] + mat[5] * m.mat[5] + mat[9] * m.mat[6] + mat[13] * m.mat[7];
		ret.mat[6] = mat[2] * m.mat[4] + mat[6] * m.mat[5] + mat[10] * m.mat[6] + mat[14] * m.mat[7];
		ret.mat[7] = mat[3] * m.mat[4] + mat[7] * m.mat[5] + mat[11] * m.mat[6] + mat[15] * m.mat[7];
		ret.mat[8] = mat[0] * m.mat[8] + mat[4] * m.mat[9] + mat[8] * m.mat[10] + mat[12] * m.mat[11];
		ret.mat[9] = mat[1] * m.mat[8] + mat[5] * m.mat[9] + mat[9] * m.mat[10] + mat[13] * m.mat[11];
		ret.mat[10] = mat[2] * m.mat[8] + mat[6] * m.mat[9] + mat[10] * m.mat[10] + mat[14] * m.mat[11];
		ret.mat[11] = mat[3] * m.mat[8] + mat[7] * m.mat[9] + mat[11] * m.mat[10] + mat[15] * m.mat[11];
		ret.mat[12] = mat[0] * m.mat[12] + mat[4] * m.mat[13] + mat[8] * m.mat[14] + mat[12] * m.mat[15];
		ret.mat[13] = mat[1] * m.mat[12] + mat[5] * m.mat[13] + mat[9] * m.mat[14] + mat[13] * m.mat[15];
		ret.mat[14] = mat[2] * m.mat[12] + mat[6] * m.mat[13] + mat[10] * m.mat[14] + mat[14] * m.mat[15];
		ret.mat[15] = mat[3] * m.mat[12] + mat[7] * m.mat[13] + mat[11] * m.mat[14] + mat[15] * m.mat[15];
		return ret;
	}

	mat4 operator+(const mat4& m) const
	{
		mat4 ret;
		ret.mat[0] = mat[0] + m.mat[0]; ret.mat[4] = mat[4] + m.mat[4]; ret.mat[8] = mat[8] + m.mat[8]; ret.mat[12] = mat[12] + m.mat[12];
		ret.mat[1] = mat[1] + m.mat[1]; ret.mat[5] = mat[5] + m.mat[5]; ret.mat[9] = mat[9] + m.mat[9]; ret.mat[13] = mat[13] + m.mat[13];
		ret.mat[2] = mat[2] + m.mat[2]; ret.mat[6] = mat[6] + m.mat[6]; ret.mat[10] = mat[10] + m.mat[10]; ret.mat[14] = mat[14] + m.mat[14];
		ret.mat[3] = mat[3] + m.mat[3]; ret.mat[7] = mat[7] + m.mat[7]; ret.mat[11] = mat[11] + m.mat[11]; ret.mat[15] = mat[15] + m.mat[15];
		return ret;
	}

	mat4 operator-(const mat4& m) const
	{
		mat4 ret;
		ret.mat[0] = mat[0] - m.mat[0]; ret.mat[4] = mat[4] - m.mat[4]; ret.mat[8] = mat[8] - m.mat[8]; ret.mat[12] = mat[12] - m.mat[12];
		ret.mat[1] = mat[1] - m.mat[1]; ret.mat[5] = mat[5] - m.mat[5]; ret.mat[9] = mat[9] - m.mat[9]; ret.mat[13] = mat[13] - m.mat[13];
		ret.mat[2] = mat[2] - m.mat[2]; ret.mat[6] = mat[6] - m.mat[6]; ret.mat[10] = mat[10] - m.mat[10]; ret.mat[14] = mat[14] - m.mat[14];
		ret.mat[3] = mat[3] - m.mat[3]; ret.mat[7] = mat[7] - m.mat[7]; ret.mat[11] = mat[11] - m.mat[11]; ret.mat[15] = mat[15] - m.mat[15];
		return ret;
	}

	// Assignment operators
	mat4& operator*=(float f)
	{
		return *this = *this * f;
	}

	mat4& operator*=(const mat4& m)
	{
		return *this = *this * m;
	}

	mat4& operator+=(const mat4& m)
	{
		return *this = *this + m;
	}

	mat4& operator-=(const mat4& m)
	{
		return *this = *this - m;
	}

	// Functions
	mat4 rotation() const
	{
		mat4 ret;
		ret.mat[0] = mat[0]; ret.mat[4] = mat[4]; ret.mat[8] = mat[8]; ret.mat[12] = 0.0f;
		ret.mat[1] = mat[1]; ret.mat[5] = mat[5]; ret.mat[9] = mat[9]; ret.mat[13] = 0.0f;
		ret.mat[2] = mat[2]; ret.mat[6] = mat[6]; ret.mat[10] = mat[10]; ret.mat[14] = 0.0f;
		ret.mat[3] = 0.0f; ret.mat[7] = 0.0f; ret.mat[11] = 0.0f; ret.mat[15] = 1.0f;
		return ret;
	}

	mat4 transpose() const
	{
		mat4 ret;
		ret.mat[0] = mat[0]; ret.mat[4] = mat[1]; ret.mat[8] = mat[2]; ret.mat[12] = mat[3];
		ret.mat[1] = mat[4]; ret.mat[5] = mat[5]; ret.mat[9] = mat[6]; ret.mat[13] = mat[7];
		ret.mat[2] = mat[8]; ret.mat[6] = mat[9]; ret.mat[10] = mat[10]; ret.mat[14] = mat[11];
		ret.mat[3] = mat[12]; ret.mat[7] = mat[13]; ret.mat[11] = mat[14]; ret.mat[15] = mat[15];
		return ret;
	}

	mat4 transpose_rotation() const
	{
		mat4 ret;
		ret.mat[0] = mat[0]; ret.mat[4] = mat[1]; ret.mat[8] = mat[2]; ret.mat[12] = mat[12];
		ret.mat[1] = mat[4]; ret.mat[5] = mat[5]; ret.mat[9] = mat[6]; ret.mat[13] = mat[13];
		ret.mat[2] = mat[8]; ret.mat[6] = mat[9]; ret.mat[10] = mat[10]; ret.mat[14] = mat[14];
		ret.mat[3] = mat[3]; ret.mat[7] = mat[7]; ret.mat[14] = mat[14]; ret.mat[15] = mat[15];
		return ret;
	}

	float det() const
	{
		return mat[0] * (mat[5] * (mat[10] * mat[15] - mat[11] * mat[14]) + mat[6] * (mat[11] * mat[13] - mat[9] * mat[15]) +
						 mat[7] * (mat[9] * mat[14] - mat[10] * mat[13])) -
			mat[1] * (mat[4] * (mat[10] * mat[15] - mat[11] * mat[14]) + mat[6] * (mat[11] * mat[12] - mat[8] * mat[15]) +
					  mat[7] * (mat[8] * mat[14] - mat[10] * mat[12])) +
			mat[2] * (mat[4] * (mat[9] * mat[15] - mat[11] * mat[13]) + mat[5] * (mat[11] * mat[12] - mat[8] * mat[15]) +
					  mat[7] * (mat[8] * mat[13] - mat[9] * mat[12])) -
			mat[3] * (mat[4] * (mat[9] * mat[14] - mat[10] * mat[13]) + mat[5] * (mat[10] * mat[12] - mat[8] * mat[14]) +
					  mat[6] * (mat[8] * mat[13] - mat[9] * mat[12]));
	}

	mat4 inverse() const
	{
		mat4 ret;
		float idet = 1.0f / det();

		ret.mat[0] = (mat[5] * mat[10] * mat[15] + mat[9] * mat[14] * mat[7] + mat[13] * mat[6] * mat[11] -
					  mat[5] * mat[14] * mat[11] - mat[9] * mat[6] * mat[15] - mat[13] * mat[10] * mat[7]) * idet;
		ret.mat[1] = -(mat[1] * mat[10] * mat[15] + mat[9] * mat[14] * mat[3] + mat[13] * mat[2] * mat[11] -
					   mat[1] * mat[14] * mat[11] - mat[9] * mat[2] * mat[15] - mat[13] * mat[10] * mat[3]) * idet;
		ret.mat[2] = (mat[1] * mat[6] * mat[15] + mat[5] * mat[14] * mat[3] + mat[13] * mat[2] * mat[7] -
					  mat[1] * mat[14] * mat[7] - mat[5] * mat[2] * mat[15] - mat[13] * mat[6] * mat[3]) * idet;
		ret.mat[3] = -(mat[1] * mat[6] * mat[11] + mat[5] * mat[10] * mat[3] + mat[9] * mat[2] * mat[7] -
					   mat[1] * mat[10] * mat[7] - mat[5] * mat[2] * mat[11] - mat[9] * mat[6] * mat[3]) * idet;

		ret.mat[4] = -(mat[4] * mat[10] * mat[15] + mat[8] * mat[14] * mat[7] + mat[12] * mat[6] * mat[11] -
					   mat[4] * mat[14] * mat[11] - mat[8] * mat[6] * mat[15] - mat[12] * mat[10] * mat[7]) * idet;
		ret.mat[5] = (mat[0] * mat[10] * mat[15] + mat[8] * mat[14] * mat[3] + mat[12] * mat[2] * mat[11] -
					  mat[0] * mat[14] * mat[11] - mat[8] * mat[2] * mat[15] - mat[12] * mat[10] * mat[3]) * idet;
		ret.mat[6] = -(mat[0] * mat[6] * mat[15] + mat[4] * mat[14] * mat[3] + mat[12] * mat[2] * mat[7] -
					   mat[0] * mat[14] * mat[7] - mat[4] * mat[2] * mat[15] - mat[12] * mat[6] * mat[3]) * idet;
		ret.mat[7] = (mat[0] * mat[6] * mat[11] + mat[4] * mat[10] * mat[3] + mat[8] * mat[2] * mat[7] -
					  mat[0] * mat[10] * mat[7] - mat[4] * mat[2] * mat[11] - mat[8] * mat[6] * mat[3]) * idet;

		ret.mat[8] = (mat[4] * mat[9] * mat[15] + mat[8] * mat[13] * mat[7] + mat[12] * mat[5] * mat[11] -
					  mat[4] * mat[13] * mat[11] - mat[8] * mat[5] * mat[15] - mat[12] * mat[9] * mat[7]) * idet,
		ret.mat[9] = -(mat[0] * mat[9] * mat[15] + mat[8] * mat[13] * mat[3] + mat[12] * mat[1] * mat[11] -
						   mat[0] * mat[13] * mat[11] - mat[8] * mat[1] * mat[15] - mat[12] * mat[9] * mat[3]) * idet;
		ret.mat[10] = (mat[0] * mat[5] * mat[15] + mat[4] * mat[13] * mat[3] + mat[12] * mat[1] * mat[7] -
					   mat[0] * mat[13] * mat[7] - mat[4] * mat[1] * mat[15] - mat[12] * mat[5] * mat[3]) * idet;
		ret.mat[11] = -(mat[0] * mat[5] * mat[11] + mat[4] * mat[9] * mat[3] + mat[8] * mat[1] * mat[7] -
						mat[0] * mat[9] * mat[7] - mat[4] * mat[1] * mat[11] - mat[8] * mat[5] * mat[3]) * idet;

		ret.mat[12] = -(mat[4] * mat[9] * mat[14] + mat[8] * mat[13] * mat[6] + mat[12] * mat[5] * mat[10] -
						mat[4] * mat[13] * mat[10] - mat[8] * mat[5] * mat[14] - mat[12] * mat[9] * mat[6]) * idet;
		ret.mat[13] = (mat[0] * mat[9] * mat[14] + mat[8] * mat[13] * mat[2] + mat[12] * mat[1] * mat[10] -
					   mat[0] * mat[13] * mat[10] - mat[8] * mat[1] * mat[14] - mat[12] * mat[9] * mat[2]) * idet;
		ret.mat[14] = -(mat[0] * mat[5] * mat[14] + mat[4] * mat[13] * mat[2] + mat[12] * mat[1] * mat[6] -
						mat[0] * mat[13] * mat[6] - mat[4] * mat[1] * mat[14] - mat[12] * mat[5] * mat[2]) * idet;
		ret.mat[15] = (mat[0] * mat[5] * mat[10] + mat[4] * mat[9] * mat[2] + mat[8] * mat[1] * mat[6] -
					   mat[0] * mat[9] * mat[6] - mat[4] * mat[1] * mat[10] - mat[8] * mat[5] * mat[2]) * idet;

		return ret;
	}

	void zero()
	{
		mat[0] = 0.0; mat[4] = 0.0; mat[8] = 0.0; mat[12] = 0.0;
		mat[1] = 0.0; mat[5] = 0.0; mat[9] = 0.0; mat[13] = 0.0;
		mat[2] = 0.0; mat[6] = 0.0; mat[10] = 0.0; mat[14] = 0.0;
		mat[3] = 0.0; mat[7] = 0.0; mat[11] = 0.0; mat[15] = 0.0;
	}

	void identity()
	{
		mat[0] = 1.0; mat[4] = 0.0; mat[8] = 0.0; mat[12] = 0.0;
		mat[1] = 0.0; mat[5] = 1.0; mat[9] = 0.0; mat[13] = 0.0;
		mat[2] = 0.0; mat[6] = 0.0; mat[10] = 1.0; mat[14] = 0.0;
		mat[3] = 0.0; mat[7] = 0.0; mat[11] = 0.0; mat[15] = 1.0;
	}

	void rotate(const vec3& axis, float angle)
	{
		float rad = DegToRad(angle);
		float c = cosf(rad);
		float s = sinf(rad);

		vec3 v = axis;
		v.normalize();

		float xx = v.x * v.x;
		float yy = v.y * v.y;
		float zz = v.z * v.z;
		float xy = v.x * v.y;
		float yz = v.y * v.z;
		float zx = v.z * v.x;
		float xs = v.x * s;
		float ys = v.y * s;
		float zs = v.z * s;

		mat[0] = (1.0f - c) * xx + c; mat[4] = (1.0f - c) * xy - zs; mat[8] = (1.0f - c) * zx + ys; mat[12] = 0.0;
		mat[1] = (1.0f - c) * xy + zs; mat[5] = (1.0f - c) * yy + c; mat[9] = (1.0f - c) * yz - xs; mat[13] = 0.0;
		mat[2] = (1.0f - c) * zx - ys; mat[6] = (1.0f - c) * yz + xs; mat[10] = (1.0f - c) * zz + c; mat[14] = 0.0;
		mat[3] = 0.0; mat[7] = 0.0; mat[11] = 0.0; mat[15] = 1.0;
	}

	void rotate_x(float angle)
	{
		float rad = DegToRad(angle);
		float c = cosf(rad);
		float s = sinf(rad);

		mat4 m;

		m.mat[0] = 1.0; m.mat[4] = 0.0; m.mat[8] = 0.0; m.mat[12] = 0.0;
		m.mat[1] = 0.0; m.mat[5] = c; m.mat[9] = -s; m.mat[13] = 0.0;
		m.mat[2] = 0.0; m.mat[6] = s; m.mat[10] = c; m.mat[14] = 0.0;
		m.mat[3] = 0.0; m.mat[7] = 0.0; m.mat[11] = 0.0; m.mat[15] = 1.0;

		this->operator*=(m);
	}

	void rotate_y(float angle)
	{
		float rad = DegToRad(angle);
		float c = cosf(rad);
		float s = sinf(rad);

		mat4 m;

		m.mat[0] = c; m.mat[4] = 0.0; m.mat[8] = s; m.mat[12] = 0.0;
		m.mat[1] = 0.0; m.mat[5] = 1.0; m.mat[9] = 0.0; m.mat[13] = 0.0;
		m.mat[2] = -s; m.mat[6] = 0.0; m.mat[10] = c; m.mat[14] = 0.0;
		m.mat[3] = 0.0; m.mat[7] = 0.0; m.mat[11] = 0.0; m.mat[15] = 1.0;

		this->operator*=(m);
	}

	void rotate_z(float angle)
	{
		float rad = DegToRad(angle);
		float c = cosf(rad);
		float s = sinf(rad);

		mat4 m;

		m.mat[0] = c; m.mat[4] = -s; m.mat[8] = 0.0; m.mat[12] = 0.0;
		m.mat[1] = s; m.mat[5] = c; m.mat[9] = 0.0; m.mat[13] = 0.0;
		m.mat[2] = 0.0; m.mat[6] = 0.0; m.mat[10] = 1.0; m.mat[14] = 0.0;
		m.mat[3] = 0.0; m.mat[7] = 0.0; m.mat[11] = 0.0; m.mat[15] = 1.0;

		this->operator*=(m);
	}

	void scale(const vec3& v)
	{
		mat4 m;
		m.mat[0] = v.x; m.mat[4] = 0.0; m.mat[8] = 0.0; m.mat[12] = 0.0;
		m.mat[1] = 0.0; m.mat[5] = v.y; m.mat[9] = 0.0; m.mat[13] = 0.0;
		m.mat[2] = 0.0; m.mat[6] = 0.0; m.mat[10] = v.z; m.mat[14] = 0.0;
		m.mat[3] = 0.0; m.mat[7] = 0.0; m.mat[11] = 0.0; m.mat[15] = 1.0;
		this->operator*=(m);
	}

	void translate(const vec3& v)
	{
		mat4 m;
		m.mat[0] = 1.0; m.mat[4] = 0.0; m.mat[8] = 0.0; m.mat[12] = v.x;
		m.mat[1] = 0.0; m.mat[5] = 1.0; m.mat[9] = 0.0; m.mat[13] = v.y;
		m.mat[2] = 0.0; m.mat[6] = 0.0; m.mat[10] = 1.0; m.mat[14] = v.z;
		m.mat[3] = 0.0; m.mat[7] = 0.0; m.mat[11] = 0.0; m.mat[15] = 1.0;
		this->operator*=(m);
	}

	void reflect(const vec4 &plane)
	{
		float x = plane.x;
		float y = plane.y;
		float z = plane.z;
		float x2 = x * 2.0f;
		float y2 = y * 2.0f;
		float z2 = z * 2.0f;

		mat4 m;
		m.mat[0] = 1.0f - x * x2; m.mat[4] = -y * x2; m.mat[8] = -z * x2; m.mat[12] = -plane.w * x2;
		m.mat[1] = -x * y2; m.mat[5] = 1.0f - y * y2; m.mat[9] = -z * y2; m.mat[13] = -plane.w * y2;
		m.mat[2] = -x * z2; m.mat[6] = -y * z2; m.mat[10] = 1.0f - z * z2; m.mat[14] = -plane.w * z2;
		m.mat[3] = 0.0; m.mat[7] = 0.0; m.mat[11] = 0.0; m.mat[15] = 1.0;

		this->operator*=(m);
	}

	void perspective_rh(float fov, float aspect, float znear, float zfar)
	{
		float yScale = 1.0f / tanf(fov * 3.1415926536f / 360.0f);
		float xScale = yScale / aspect;
		mat[0] = xScale;	mat[4] = 0.0;		mat[8] = 0.0; mat[12] = 0.0;
		mat[1] = 0.0;		mat[5] = yScale;	mat[9] = 0.0; mat[13] = 0.0;
		mat[2] = 0.0;		mat[6] = 0.0;		mat[10] = zfar / (znear - zfar); mat[14] = znear * zfar / (znear - zfar);
		mat[3] = 0.0;		mat[7] = 0.0;		mat[11] = -1.0; mat[15] = 0.0;
	}

	void perspective_lh(float fov, float aspect, float znear, float zfar)
	{
		float yScale = 1.0f / tanf(fov * 3.1415926536f / 360.0f);
		float xScale = yScale / aspect;
		mat[0] = xScale;	mat[4] = 0.0;		mat[8] = 0.0; mat[12] = 0.0;
		mat[1] = 0.0;		mat[5] = yScale;	mat[9] = 0.0; mat[13] = 0.0;
		mat[2] = 0.0;		mat[6] = 0.0;		mat[10] = zfar / (zfar - znear); mat[14] = -znear * zfar / (zfar - znear);
		mat[3] = 0.0;		mat[7] = 0.0;		mat[11] = 1.0; mat[15] = 0.0;
	}

	void look_at(const vec3& eye, const vec3& dir, const vec3& up)
	{
		vec3 x, y, z;
		z = eye - dir;
		z.normalize();
		x.cross(up, z);
		x.normalize();
		y.cross(z, x);
		y.normalize();
		mat[0] = x.x; mat[4] = x.y; mat[8] = x.z; mat[12] = -dot(x, eye);
		mat[1] = y.x; mat[5] = y.y; mat[9] = y.z; mat[13] = -dot(y, eye);
		mat[2] = z.x; mat[6] = z.y; mat[10] = z.z; mat[14] = -dot(z, eye);
		mat[3] = 0.0; mat[7] = 0.0; mat[11] = 0.0; mat[15] = 1.0;
	}

	/*2/w  0    0           0
		0    2/h  0           0
		0    0    1/(zf-zn)   0
		0    0    zn/(zn-zf)  1*/
	void ortho(float w, float h, float znear, float zfar)
	{
		mat4 m0;
		m0.mat[0] = 2 / w; m0.mat[4] = 0.0; m0.mat[8] = 0.0; m0.mat[12] = 0.0;
		m0.mat[1] = 0.0; m0.mat[5] = 2 / h; m0.mat[9] = 0.0; m0.mat[13] = 0.0;
		m0.mat[2] = 0.0; m0.mat[6] = 0.0; m0.mat[10] = 1.0f / (zfar - znear); m0.mat[14] = znear / (znear - zfar);
		m0.mat[3] = 0.0; m0.mat[7] = 0.0; m0.mat[11] = 0.0; m0.mat[15] = 1.0;
		*this = m0;
	}

	/*
	2/(r-l)      0            0           0
	0            2/(t-b)      0           0
	0            0            1/(zf-zn)   0
	(l+r)/(l-r)  (t+b)/(b-t)  zn/(zn-zf)  l
	*/
	void ortho_lh(float l, float r, float b, float t, float znear, float zfar)
	{
		mat4 m0;
		m0.mat[0] = 2 / (r - l); m0.mat[4] = 0.0; m0.mat[8] = 0.0; m0.mat[12] = (l + r) / (l - r);
		m0.mat[1] = 0.0; m0.mat[5] = 2 / (t - b); m0.mat[9] = 0.0; m0.mat[13] = (t + b) / (b - t);
		m0.mat[2] = 0.0; m0.mat[6] = 0.0; m0.mat[10] = 1.0f / (zfar - znear); m0.mat[14] = znear / (znear - zfar);
		m0.mat[3] = 0.0; m0.mat[7] = 0.0; m0.mat[11] = 0.0; m0.mat[15] = 1.0;
		*this = m0;
	}

	void ortho_rh(float l, float r, float b, float t, float znear, float zfar)
	{
		mat4 m0;
		m0.mat[0] = 2 / (r - l); m0.mat[4] = 0.0; m0.mat[8] = 0.0; m0.mat[12] = (l + r) / (l - r);
		m0.mat[1] = 0.0; m0.mat[5] = 2 / (t - b); m0.mat[9] = 0.0; m0.mat[13] = (t + b) / (b - t);
		m0.mat[2] = 0.0; m0.mat[6] = 0.0; m0.mat[10] = 1.0f / (znear - zfar); m0.mat[14] = znear / (znear - zfar);
		m0.mat[3] = 0.0; m0.mat[7] = 0.0; m0.mat[11] = 0.0; m0.mat[15] = 1.0;
		*this = m0;
	}

	void normalize_rotation()
	{
		float intLen;

		intLen = 1.0f / sqrtf(mat[0] * mat[0] + mat[1] * mat[1] + mat[2] * mat[2]);
		mat[0] *= intLen;
		mat[1] *= intLen;
		mat[2] *= intLen;

		intLen = 1.0f / sqrtf(mat[4] * mat[4] + mat[5] * mat[5] + mat[6] * mat[6]);
		mat[4] *= intLen;
		mat[5] *= intLen;
		mat[6] *= intLen;

		intLen = 1.0f / sqrtf(mat[8] * mat[8] + mat[9] * mat[9] + mat[10] * mat[10]);
		mat[8] *= intLen;
		mat[9] *= intLen;
		mat[10] *= intLen;
	}

	vec4& row0()
	{
		return *(vec4*)&mat[0];
	}

	vec4& row1()
	{
		return *(vec4*)&mat[4];
	}

	vec4& row2()
	{
		return *(vec4*)&mat[8];
	}

	vec4& row3()
	{
		return *(vec4*)&mat[12];
	}

	float mat[16];
};

inline mat3::mat3(const mat4 &m)
{
	mat[0] = m.mat[0]; mat[3] = m.mat[4]; mat[6] = m.mat[8];
	mat[1] = m.mat[1]; mat[4] = m.mat[5]; mat[7] = m.mat[9];
	mat[2] = m.mat[2]; mat[5] = m.mat[6]; mat[8] = m.mat[10];
}

inline void mul(mat4 &ret, const mat4 &n, const mat4 &m)
{
	ret.mat[0] = n.mat[0] * m.mat[0] + n.mat[4] * m.mat[1] + n.mat[8] * m.mat[2] + n.mat[12] * m.mat[3];
	ret.mat[1] = n.mat[1] * m.mat[0] + n.mat[5] * m.mat[1] + n.mat[9] * m.mat[2] + n.mat[13] * m.mat[3];
	ret.mat[2] = n.mat[2] * m.mat[0] + n.mat[6] * m.mat[1] + n.mat[10] * m.mat[2] + n.mat[14] * m.mat[3];
	ret.mat[3] = n.mat[3] * m.mat[0] + n.mat[7] * m.mat[1] + n.mat[11] * m.mat[2] + n.mat[15] * m.mat[3];
	ret.mat[4] = n.mat[0] * m.mat[4] + n.mat[4] * m.mat[5] + n.mat[8] * m.mat[6] + n.mat[12] * m.mat[7];
	ret.mat[5] = n.mat[1] * m.mat[4] + n.mat[5] * m.mat[5] + n.mat[9] * m.mat[6] + n.mat[13] * m.mat[7];
	ret.mat[6] = n.mat[2] * m.mat[4] + n.mat[6] * m.mat[5] + n.mat[10] * m.mat[6] + n.mat[14] * m.mat[7];
	ret.mat[7] = n.mat[3] * m.mat[4] + n.mat[7] * m.mat[5] + n.mat[11] * m.mat[6] + n.mat[15] * m.mat[7];
	ret.mat[8] = n.mat[0] * m.mat[8] + n.mat[4] * m.mat[9] + n.mat[8] * m.mat[10] + n.mat[12] * m.mat[11];
	ret.mat[9] = n.mat[1] * m.mat[8] + n.mat[5] * m.mat[9] + n.mat[9] * m.mat[10] + n.mat[13] * m.mat[11];
	ret.mat[10] = n.mat[2] * m.mat[8] + n.mat[6] * m.mat[9] + n.mat[10] * m.mat[10] + n.mat[14] * m.mat[11];
	ret.mat[11] = n.mat[3] * m.mat[8] + n.mat[7] * m.mat[9] + n.mat[11] * m.mat[10] + n.mat[15] * m.mat[11];
	ret.mat[12] = n.mat[0] * m.mat[12] + n.mat[4] * m.mat[13] + n.mat[8] * m.mat[14] + n.mat[12] * m.mat[15];
	ret.mat[13] = n.mat[1] * m.mat[12] + n.mat[5] * m.mat[13] + n.mat[9] * m.mat[14] + n.mat[13] * m.mat[15];
	ret.mat[14] = n.mat[2] * m.mat[12] + n.mat[6] * m.mat[13] + n.mat[10] * m.mat[14] + n.mat[14] * m.mat[15];
	ret.mat[15] = n.mat[3] * m.mat[12] + n.mat[7] * m.mat[13] + n.mat[11] * m.mat[14] + n.mat[15] * m.mat[15];
}

inline vec3 mul_m4_v3(const mat4 &m, const vec3 &v)
{
	vec3 ret;
	ret.x = m.mat[0] * v.x + m.mat[4] * v.y + m.mat[8] * v.z + m.mat[12];
	ret.y = m.mat[1] * v.x + m.mat[5] * v.y + m.mat[9] * v.z + m.mat[13];
	ret.z = m.mat[2] * v.x + m.mat[6] * v.y + m.mat[10] * v.z + m.mat[14];
	return ret;
}

inline vec3 mul_m4_v3(const vec3 &v, const mat4 &m)
{
	vec3 ret;
	ret.x = m.mat[0] * v.x + m.mat[1] * v.y + m.mat[2] * v.z + m.mat[3];
	ret.y = m.mat[4] * v.x + m.mat[5] * v.y + m.mat[6] * v.z + m.mat[7];
	ret.z = m.mat[8] * v.x + m.mat[9] * v.y + m.mat[10] * v.z + m.mat[11];
	return ret;
}

inline void mul_m4_v3(vec3 &ret, const vec3 &v, const mat4 &m)
{
	ret.x = m.mat[0] * v.x + m.mat[1] * v.y + m.mat[2] * v.z + m.mat[3];
	ret.y = m.mat[4] * v.x + m.mat[5] * v.y + m.mat[6] * v.z + m.mat[7];
	ret.z = m.mat[8] * v.x + m.mat[9] * v.y + m.mat[10] * v.z + m.mat[11];
}

inline void mul_m4_v3_trans(vec3 &ret, const vec3 &v, const mat4 &m)
{
	ret.x = m.mat[0] * v.x + m.mat[4] * v.y + m.mat[8] * v.z + m.mat[12];
	ret.y = m.mat[1] * v.x + m.mat[5] * v.y + m.mat[9] * v.z + m.mat[13];
	ret.z = m.mat[2] * v.x + m.mat[6] * v.y + m.mat[10] * v.z + m.mat[14];
}

inline void mul_m4_v3(vec4 &ret, const vec3 &v, const mat4 &m)
{
	ret.x = m.mat[0] * v.x + m.mat[1] * v.y + m.mat[2] * v.z + m.mat[3];
	ret.y = m.mat[4] * v.x + m.mat[5] * v.y + m.mat[6] * v.z + m.mat[7];
	ret.z = m.mat[8] * v.x + m.mat[9] * v.y + m.mat[10] * v.z + m.mat[11];
	ret.w = m.mat[12] * v.x + m.mat[13] * v.y + m.mat[14] * v.z + m.mat[15];
}

#undef DegToRad
