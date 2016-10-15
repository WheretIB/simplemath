#pragma once

#include "matrix.h"

#define Epsilon() 1e-6f
#define DegToRad(x) ((x) * 3.1415926536f / 180.0f)
#define RadToDeg(x) ((x) * 180.0f / 3.1415926536f)

struct quat
{
	quat(): x(0), y(0), z(0), w(1)
	{
	}

	quat(const mat3& m)
	{
		float trace = m.mat[0] + m.mat[4] + m.mat[8];

		if(trace > 0.0)
		{
			float s = sqrtf(trace + 1.0f);

			w = 0.5f * s;
			s = 0.5f / s;

			x = (m.mat[5] - m.mat[7]) * s;
			y = (m.mat[6] - m.mat[2]) * s;
			z = (m.mat[1] - m.mat[3]) * s;
		}
		else
		{
			static int next[3] = { 1, 2, 0 };

			int i = 0;

			if(m.mat[4] > m.mat[0])
				i = 1;

			if(m.mat[8] > m.mat[3 * i + i])
				i = 2;

			int j = next[i];
			int k = next[j];

			float s = sqrtf(m.mat[3 * i + i] - m.mat[3 * j + j] - m.mat[3 * k + k] + 1.0f);

			((float*)&x)[i] = 0.5f * s;

			if(s != 0)
				s = 0.5f / s;

			w = (m.mat[3 * j + k] - m.mat[3 * k + j]) * s;

			((float*)&x)[j] = (m.mat[3 * i + j] + m.mat[3 * j + i]) * s;
			((float*)&x)[k] = (m.mat[3 * i + k] + m.mat[3 * k + i]) * s;
		}
	}

	quat(float nx, float ny, float nz, float nw): x(nx), y(ny), z(nz), w(nw)
	{
	}

	bool operator==(const quat& q) const
	{
		return x == q.x && y == q.y && z == q.z && w == q.w;
	}

	bool operator!=(const quat& q) const
	{
		return x != q.x || y != q.y || z != q.z || w != q.w;
	}

	quat operator*(const quat& q) const
	{
		quat ret;
		ret.x = w * q.x + y * q.z - z * q.y + x * q.w;
		ret.y = w * q.y + z * q.x - x * q.z + y * q.w;
		ret.z = w * q.z + x * q.y - y * q.x + z * q.w;
		ret.w = w * q.w - x * q.x - y * q.y - z * q.z;
		return ret;
	}

	// Create a quaternion that represents rotation around axis "dir" by angle
	quat& set(const vec3& dir, float angle)
	{
		float length = dir.length();

		if(length != 0.0f)
		{
			length = 1.0f / length;

			float sinAngle = sinf(DegToRad(angle) / 2.0f);

			x = dir.x * length * sinAngle;
			y = dir.y * length * sinAngle;
			z = dir.z * length * sinAngle;

			w = cosf(DegToRad(angle) / 2.0f);
		}
		else
		{
			x = y = z = 0.0f;
			w = 1.0f;
		}

		return *this;
	}

	quat& set(float x, float y, float z, float angle)
	{
		return set(vec3(x, y, z), angle);
	}

	// Create a quaternion that represents transformation that rotates vec3(1, 0, 0) into "dir"
	void set_from_direction(const vec3& dir)
	{
		set_from_direction(vec3(1, 0, 0), dir);
	}

	// Create a quaternion that represents transformation that rotates "from" into "to"
	void set_from_direction(const vec3& from, const vec3& to)
	{
		vec3 f = ::normalize(from);
		vec3 t = ::normalize(to);

		float cosAngle = dot(f, t);

		vec3 axis = cross(f, t);

		float value = acosf(cosAngle);

		set(axis, RadToDeg(value));
	}

	void slerp(const quat& q0, const quat& q1, float t)
	{
		float k0, k1;
		
		float cosomega = q0.x * q1.x + q0.y * q1.y + q0.z * q1.z + q0.w * q1.w;

		quat q;

		if(cosomega < 0.0f)
		{
			cosomega = -cosomega;

			q.x = -q1.x;
			q.y = -q1.y;
			q.z = -q1.z;
			q.w = -q1.w;
		}
		else
		{
			q.x = q1.x;
			q.y = q1.y;
			q.z = q1.z;
			q.w = q1.w;
		}

		if(1.0 - cosomega > Epsilon())
		{
			float omega = acosf(cosomega); 
			float sinomega = sinf(omega);

			k0 = sinf((1.0f - t) * omega) / sinomega;
			k1 = sinf(t * omega) / sinomega;
		}
		else
		{
			k0 = 1.0f - t;
			k1 = t;
		}

		x = q0.x * k0 + q.x * k1;
		y = q0.y * k0 + q.y * k1;
		z = q0.z * k0 + q.z * k1;
		w = q0.w * k0 + q.w * k1;
	}

	mat3 to_matrix() const
	{
		mat3 ret;

		float x2 = x + x;
		float y2 = y + y;
		float z2 = z + z;
		float xx = x * x2;
		float yy = y * y2;
		float zz = z * z2;
		float xy = x * y2;
		float yz = y * z2;
		float xz = z * x2;
		float wx = w * x2;
		float wy = w * y2;
		float wz = w * z2;

		ret.mat[0] = 1.0f - (yy + zz); ret.mat[3] = xy - wz; ret.mat[6] = xz + wy;
		ret.mat[1] = xy + wz; ret.mat[4] = 1.0f - (xx + zz); ret.mat[7] = yz - wx;
		ret.mat[2] = xz - wy; ret.mat[5] = yz + wx; ret.mat[8] = 1.0f - (xx + yy);

		return ret;
	}

	void normalize()
	{
		float magn = float(1.0 / sqrtf(x * x + y * y + z * z + w * w));

		x *= magn;
		y *= magn;
		z *= magn;
		w *= magn;
	}

	quat conjugate()
	{
		quat ret = *this;

		ret.x = -ret.x;
		ret.y = -ret.y;
		ret.z = -ret.z;

		return ret;
	}

	vec3 transform_vector(const vec3& v)
	{
		vec3 uv(y * v.z - z * v.y,
				z * v.x - x * v.z,
				x * v.y - y * v.x);

		vec3 uuv(y * uv.z - z * uv.y,
				 z * uv.x - x * uv.z,
				 x * uv.y - y * uv.x);

		uv *= w;
		uv += uuv;
		uv *= 2;

		return v + uv;
	}

	float x, y, z, w;
};

#undef Epsilon
#undef DegToRad
#undef RadToDeg
