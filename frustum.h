#pragma once

#include "plane.h"
#include "aabb.h"

struct frustum
{
	enum
	{
		PLANE_LEFT,
		PLANE_RIGHT,
		PLANE_BOTTOM,
		PLANE_TOP,
		PLANE_NEAR,
		PLANE_FAR
	};

	void calculate_points(const mat4& viewProjection, float minz = 0.0f)
	{
		mat4 m = viewProjection.inverse();

		vec3	minp(-1.0, -1.0, minz);
		vec3	maxp(1.0, 1.0, 1.0);

		pt[0] = vec3(minp.x, minp.y, minp.z);
		pt[1] = vec3(maxp.x, minp.y, minp.z);
		pt[2] = vec3(minp.x, maxp.y, minp.z);
		pt[3] = vec3(maxp.x, maxp.y, minp.z);
		pt[4] = vec3(minp.x, minp.y, maxp.z);
		pt[5] = vec3(maxp.x, minp.y, maxp.z);
		pt[6] = vec3(minp.x, maxp.y, maxp.z);
		pt[7] = vec3(maxp.x, maxp.y, maxp.z);

		for(int i = 0; i < 8; i++)
			pt[i] = m * pt[i];
	}

	void calculate_planes(const mat4& viewProjection)
	{
		mat4 m = viewProjection.transpose();

		p[PLANE_LEFT].pl = m.row3() + m.row0();
		p[PLANE_RIGHT].pl = m.row3() - m.row0();

		p[PLANE_BOTTOM].pl = m.row3() + m.row1();
		p[PLANE_TOP].pl = m.row3() - m.row1();

		p[PLANE_NEAR].pl = m.row2();
		p[PLANE_FAR].pl = m.row3() - m.row2();

		for(int i = 0; i < 6; i++)
			p[i].normalize();
	}

	// Visibility tests
	bool point_inside(const vec3& pos)
	{
		for(int i = 0; i < 6; i++)
		{
			if(pos.x * p[i].pl.x + pos.y * p[i].pl.y + pos.z * p[i].pl.z + p[i].pl.w <= 0.0f)
				return false;
		}

		return true;
	}

	bool point_inside(const vec4& pos)
	{
		for(int i = 0; i < 6; i++)
		{
			if(pos.x * p[i].pl.x + pos.y * p[i].pl.y + pos.z * p[i].pl.z + p[i].pl.w <= 0.0f)
				return false;
		}

		return true;
	}

	unsigned point_outside_plane(const vec3& pos)
	{
		for(int i = 0; i < 6; i++)
		{
			if(pos.x * p[i].pl.x + pos.y * p[i].pl.y + pos.z * p[i].pl.z + p[i].pl.w <= 0.0f)
				return i;
		}

		return ~0u;
	}

	unsigned point_outside_plane(const vec4& pos)
	{
		for(int i = 0; i < 6; i++)
		{
			if(pos.x * p[i].pl.x + pos.y * p[i].pl.y + pos.z * p[i].pl.z + p[i].pl.w <= 0.0f)
				return i;
		}

		return ~0u;
	}

	bool sphere_inside(const vec3& pos, float radius)
	{
		for(int i = 0; i < 6; i++)
		{
			if(pos.x * p[i].pl.x + pos.y * p[i].pl.y + pos.z * p[i].pl.z + p[i].pl.w <= -radius)
				return false;
		}

		return true;
	}

	bool sprite_inside(const vec3& p1, const vec3& p2, const vec3& p3, const vec3& p4)
	{
		for(int i = 0; i < 6; i++)
		{
			bool inside = false;

			if(dot(p1, p[i].pl) > 0)
				inside = true;
			else if(dot(p2, p[i].pl) > 0)
				inside = true;
			else if(dot(p3, p[i].pl) > 0)
				inside = true;
			else if(dot(p4, p[i].pl) > 0)
				inside = true;

			if(!inside)
				return false;
		}

		return true;
	}

	bool aabb_inside(const aabb& box)
	{
		float minX = box.center.x - box.size.x;
		float minY = box.center.y - box.size.y;
		float minZ = box.center.z - box.size.z;

		float maxX = box.center.x + box.size.x;
		float maxY = box.center.y + box.size.y;
		float maxZ = box.center.z + box.size.z;

		// Get aabb points
		float points[][3] =
		{
			{ minX, minY, minZ },
			{ maxX, minY, minZ },
			{ maxX, maxY, minZ },
			{ minX, maxY, minZ },

			{ minX, minY, maxZ },
			{ maxX, minY, maxZ },
			{ maxX, maxY, maxZ },
			{ minX, maxY, maxZ }
		};

		for(int i = 0; i < 6; i++)
		{
			bool inside = false;

			for(int j = 0; j < 8; j++)
			{
				if(points[j][0] * p[i].pl.x + points[j][1] * p[i].pl.y + points[j][2] * p[i].pl.z + p[i].pl.w > 0)
				{
					inside = true;
					break;
				}
			}

			if(!inside)
				return false;
		}

		return true;
	}

	vec3 pt[8];
	plane p[6];
};
