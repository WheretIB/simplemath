#pragma once

#include <math.h>

#define Epsilon() 1e-6f

struct vec2;
struct vec3;
struct vec4;

/********************************************************************************/
/*								vec2											*/
/********************************************************************************/

struct vec2
{
	vec2(): x(0.0f), y(0.0f)
	{
	}

	explicit vec2(float v): x(v), y(v)
	{
	}

	vec2(const vec2& v): x(v.x), y(v.y)
	{
	}

	explicit vec2(const float* v): x(v[0]), y(v[1])
	{
	}

	vec2(float x, float y): x(x), y(y)
	{
	}

	explicit vec2(const vec3& v);
	explicit vec2(const vec4& v);

	// Unary operators
	const vec2 operator-() const
	{
		return vec2(-x, -y);
	}

	// Binary operators
	const vec2 operator*(float a) const
	{
		return vec2(x*a, y*a);
	}

	const vec2 operator/(float a) const
	{
		return vec2(x / a, y / a);
	}

	const vec2 operator+(const vec2& v) const
	{
		return vec2(x + v.x, y + v.y);
	}

	const vec2 operator-(const vec2& v) const
	{
		return vec2(x - v.x, y - v.y);
	}

	bool operator==(const vec2& v) const
	{
		return v.x == x && v.y == y;
	}

	bool operator!=(const vec2& v) const
	{
		return !(*this == v);
	}

	// Assignment operators
	vec2& operator*=(float a)
	{
		return (*this = *this * a);
	}

	vec2& operator/=(float a)
	{
		return (*this = *this / a);
	}

	vec2& operator+=(const vec2& v)
	{
		return (*this = *this + v);
	}

	vec2& operator-=(const vec2& v)
	{
		return (*this = *this - v);
	}

	// Functions
	float length() const
	{
		return sqrtf(x * x + y * y);
	}

	float length_squared() const
	{
		return x * x + y * y;
	}

	float normalize()
	{
		float len = length();

		if(len < Epsilon())
			return 0.0f;

		float inv = 1.0f / len;

		x *= inv;
		y *= inv;

		return len;
	}

	vec2 normalized() const
	{
		float len = length();

		if(len < Epsilon())
			return *this;

		float inv = 1.0f / len;

		return *this * inv;
	}

	vec2 rotated(float radians) const
	{
		return vec2(x * cosf(radians) - y * sinf(radians), x * sinf(radians) + y * cosf(radians));
	}

	float x, y;
};

/********************************************************************************/
/*								vec3											*/
/********************************************************************************/

struct vec3
{
	vec3(): x(0.0f), y(0.0f), z(0.0f)
	{
	}

	explicit vec3(float v): x(v), y(v), z(v)
	{
	}

	vec3(const vec2& v, float z): x(v.x), y(v.y), z(z)
	{
	}

	vec3(const vec3& v): x(v.x), y(v.y), z(v.z)
	{
	}

	explicit vec3(const float* v): x(v[0]), y(v[1]), z(v[2])
	{
	}

	vec3(float x, float y, float z): x(x), y(y), z(z)
	{
	}

	explicit vec3(const vec4& v);

	// Unary operators
	const vec3 operator-() const
	{
		return vec3(-x, -y, -z);
	}

	// Binary operators
	const vec3 operator*(float a) const
	{
		return vec3(x*a, y*a, z*a);
	}

	const vec3 operator/(float a) const
	{
		return vec3(x / a, y / a, z / a);
	}

	const vec3 operator+(const vec3& v) const
	{
		return vec3(x + v.x, y + v.y, z + v.z);
	}

	const vec3 operator-(const vec3& v) const
	{
		return vec3(x - v.x, y - v.y, z - v.z);
	}

	const vec3 operator*(const vec3& v) const
	{
		return vec3(x*v.x, y*v.y, z*v.z);
	}

	const vec3 operator/(const vec3& v) const
	{
		return vec3(x / v.x, y / v.y, z / v.z);
	}

	bool operator==(const vec3& v) const
	{
		return v.x == x && v.y == y && v.z == z;
	}

	bool operator!=(const vec3& v) const
	{
		return !(*this == v);
	}

	// Assignment operators
	vec3& operator*=(float a)
	{
		return (*this = *this * a);
	}

	vec3& operator/=(float a)
	{
		return (*this = *this / a);
	}

	vec3& operator+=(const vec3& v)
	{
		return (*this = *this + v);
	}

	vec3& operator-=(const vec3& v)
	{
		return (*this = *this - v);
	}

	// Functions
	float length() const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	float length_squared() const
	{
		return x * x + y * y + z * z;
	}

	float normalize()
	{
		float len = length();

		if(len < Epsilon())
			return 0.0f;

		float inv = 1.0f / len;

		x *= inv;
		y *= inv;
		z *= inv;

		return len;
	}

	vec3 normalized() const
	{
		float len = length();

		if(len < Epsilon())
			return *this;

		float inv = 1.0f / len;

		return *this * inv;
	}

	float dot(const vec3& v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}

	vec3 cross(const vec3& v2) const
	{
		vec3 ret;
		ret.x = y * v2.z - z * v2.y;
		ret.y = z * v2.x - x * v2.z;
		ret.z = x * v2.y - y * v2.x;
		return ret;
	}

	void cross(const vec3& v1, const vec3& v2)
	{
		x = v1.y * v2.z - v1.z * v2.y;
		y = v1.z * v2.x - v1.x * v2.z;
		z = v1.x * v2.y - v1.y * v2.x;
	}

	// Swizzles
	vec2 xy() const
	{
		return vec2(x, y);
	}

	vec2 xx() const
	{
		return vec2(x, x);
	}

	vec2 yy() const
	{
		return vec2(y, y);
	}

	float x, y, z;
};

/********************************************************************************/
/*								vec4											*/
/********************************************************************************/

struct vec4
{
	vec4(): x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{
	}

	explicit vec4(float v): x(v), y(v), z(v), w(v)
	{
	}

	vec4(const vec2& v, float z, float w): x(v.x), y(v.y), z(z), w(w)
	{
	}

	vec4(const vec3& v, float w): x(v.x), y(v.y), z(v.z), w(w)
	{
	}

	explicit vec4(const vec2& v): x(v.x), y(v.y), z(0.0f), w(1.0f)
	{
	}

	explicit vec4(const vec3& v): x(v.x), y(v.y), z(v.z), w(1.0f)
	{
	}

	explicit vec4(const float* v): x(v[0]), y(v[1]), z(v[2]), w(v[3])
	{
	}

	vec4(float x, float y, float z, float w = 1.0f): x(x), y(y), z(z), w(w)
	{
	}

	// Unary operators
	const vec4 operator-() const
	{
		return vec4(-x, -y, -z, -w);
	}

	// Binary operators
	const vec4 operator*(float a) const
	{
		return vec4(x*a, y*a, z*a, w*a);
	}

	const vec4 operator/(float a) const
	{
		return vec4(x / a, y / a, z / a, w / a);
	}

	const vec4 operator+(const vec4& v) const
	{
		return vec4(x + v.x, y + v.y, z + v.z, w + v.w);
	}

	const vec4 operator-(const vec4& v) const
	{
		return vec4(x - v.x, y - v.y, z - v.z, w - v.w);
	}

	const vec4 operator*(const vec4& v) const
	{
		return vec4(x*v.x, y*v.y, z*v.z, w*v.w);
	}

	bool operator==(const vec4& v) const
	{
		return v.x == x && v.y == y && v.z == z && v.w == w;
	}

	bool operator!=(const vec4& v) const
	{
		return !(*this == v);
	}

	// Assignment operators
	vec4& operator*=(float a)
	{
		return (*this = *this * a);
	}

	vec4& operator/=(float a)
	{
		return (*this = *this / a);
	}

	vec4& operator+=(const vec4& v)
	{
		return (*this = *this + v);
	}

	vec4& operator-=(const vec4& v)
	{
		return (*this = *this - v);
	}

	vec4& operator*=(const vec4& v)
	{
		return (*this = *this * v);
	}

	// Functions
	float length() const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	float length_squared() const
	{
		return x * x + y * y + z * z;
	}

	float normalize()
	{
		float len = length();

		if(len < Epsilon())
			return 0.0f;

		float inv = 1.0f / len;

		x *= inv;
		y *= inv;
		z *= inv;

		return len;
	}

	vec4 normalized() const
	{
		float len = length();

		if(len < Epsilon())
			return *this;

		float inv = 1.0f / len;

		return vec4(xyz() * inv, 1.0f);
	}

	// Swizzles
	vec2 xy() const
	{
		return vec2(x, y);
	}

	vec3 xyz() const
	{
		return vec3(x, y, z);
	}

	vec3 xxx() const
	{
		return vec3(x, x, x);
	}

	vec3 yyy() const
	{
		return vec3(y, y, y);
	}

	vec3 zzz() const
	{
		return vec3(z, z, z);
	}

	vec3 www() const
	{
		return vec3(w, w, w);
	}

	float x, y, z, w;
};

// Additional functions
inline vec2::vec2(const vec3& v)
{
	x = v.x;
	y = v.y;
}

inline vec2::vec2(const vec4& v)
{
	x = v.x;
	y = v.y;
}

inline vec3::vec3(const vec4& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

inline vec2 operator*(const float f, const vec2& v)
{
	return vec2(f * v.x, f * v.y);
}

inline vec3 operator*(const float f, const vec3& v)
{
	return vec3(f * v.x, f * v.y, f * v.z);
}

inline vec4 operator*(const float f, const vec4& v)
{
	return vec4(f * v.x, f * v.y, f * v.z, f * v.w);
}

inline vec2 operator/(const float f, const vec2& v)
{
	return vec2(f / v.x, f / v.y);
}

inline vec3 operator/(const float f, const vec3& v)
{
	return vec3(f / v.x, f / v.y, f / v.z);
}

inline vec4 operator/(const float f, const vec4& v)
{
	return vec4(f / v.x, f / v.y, f / v.z, f / v.w);
}

inline vec2 normalize(vec2 v)
{
	v.normalize();
	return v;
}

inline vec3 normalize(vec3 v)
{
	v.normalize();
	return v;
}

inline vec4 normalize(vec4 v)
{
	v.normalize();
	return v;
}

inline vec3 cross(const vec3& v1, const vec3& v2)
{
	vec3 ret;
	ret.x = v1.y * v2.z - v1.z * v2.y;
	ret.y = v1.z * v2.x - v1.x * v2.z;
	ret.z = v1.x * v2.y - v1.y * v2.x;
	return ret;
}

inline float dot(const vec2& v1, const vec2& v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

inline float dot(const vec3& v1, const vec3& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline float dot(const vec4& v1, const vec4& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

inline float dot(const vec3& v1, const vec4& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v2.w;
}

inline vec2 saturate(const vec2& v)
{
	vec2 ret = v;

	if(ret.x < 0.0f)
		ret.x = 0.0f;
	else if(ret.x > 1.0f)
		ret.x = 1.0f;

	if(ret.y < 0.0f)
		ret.y = 0.0f;
	else if(ret.y > 1.0f)
		ret.y = 1.0f;

	return ret;
}

inline vec3 saturate(const vec3& v)
{
	vec3 ret = v;

	if(ret.x < 0.0f)
		ret.x = 0.0f;
	else if(ret.x > 1.0f)
		ret.x = 1.0f;

	if(ret.y < 0.0f)
		ret.y = 0.0f;
	else if(ret.y > 1.0f)
		ret.y = 1.0f;

	if(ret.z < 0.0f)
		ret.z = 0.0f;
	else if(ret.z > 1.0f)
		ret.z = 1.0f;

	return ret;
}

inline vec4 saturate(const vec4& v)
{
	vec4 ret = v;

	if(ret.x < 0.0f)
		ret.x = 0.0f;
	else if(ret.x > 1.0f)
		ret.x = 1.0f;

	if(ret.y < 0.0f)
		ret.y = 0.0f;
	else if(ret.y > 1.0f)
		ret.y = 1.0f;

	if(ret.z < 0.0f)
		ret.z = 0.0f;
	else if(ret.z > 1.0f)
		ret.z = 1.0f;

	if(ret.w < 0.0f)
		ret.w = 0.0f;
	else if(ret.w > 1.0f)
		ret.w = 1.0f;

	return ret;
}

inline vec2 pow(const vec2& v, float f)
{
	return vec2(powf(v.x, f), powf(v.y, f));
}

inline vec3 pow(const vec3& v, float f)
{
	return vec3(powf(v.x, f), powf(v.y, f), powf(v.z, f));
}

inline vec4 pow(const vec4& v, float f)
{
	return vec4(powf(v.x, f), powf(v.y, f), powf(v.z, f), powf(v.w, f));
}

inline vec3 normal(const vec3& a, const vec3& b, const vec3& c)
{
	vec3 ret;

	ret.cross(b - a, c - a);
	ret.normalize();

	return ret;
}

inline float triangle_area(const vec3& a, const vec3& b, const vec3& c)
{
	return cross(a - b, c - b).length() / 2.0f;
}

#undef Epsilon
