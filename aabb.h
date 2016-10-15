#pragma once

#include "vector.h"
#include "matrix.h"

struct aabb
{
	aabb()
	{
	}

	aabb(const vec3& c, const vec3& s)
	{
		center = c; size = s;
	}

	vec3 min_point() const
	{
		return center - size;
	}

	vec3 max_point() const
	{
		return center + size;
	}

	float radius() const
	{
		return size.length();
	}

	float radius_squared() const
	{
		return dot(size, size);
	}

	void merge(const aabb& b)
	{
		vec3 minA = min_point();
		vec3 maxA = max_point();

		vec3 minB = b.min_point();
		vec3 maxB = b.max_point();

		minA.x = minA.x < minB.x ? minA.x : minB.x;
		minA.y = minA.y < minB.y ? minA.y : minB.y;
		minA.z = minA.z < minB.z ? minA.z : minB.z;

		maxA.x = maxA.x > maxB.x ? maxA.x : maxB.x;
		maxA.y = maxA.y > maxB.y ? maxA.y : maxB.y;
		maxA.z = maxA.z > maxB.z ? maxA.z : maxB.z;
		center = (minA + maxA) / 2.0;
		size = (maxA - minA) / 2.0;
	}

	void mul(const mat4& mat)
	{
		mat3 absMat(mat);

		for(unsigned i = 0; i < 9; i++)
			absMat.mat[i] = absMat.mat[i] < 0.0f ? -absMat.mat[i] : absMat.mat[i];

		center = mat * center;
		size = absMat * size;
	}

	vec3 center;
	vec3 size;
};
