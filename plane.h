#pragma once

#include <math.h>

#include "vector.h"
#include "matrix.h"
#include "aabb.h"

#define Epsilon() 1e-6f

struct line;
struct plane;

struct line
{
	line()
	{
	}

	line(const vec3& a, const vec3& b)
	{
		p = a; n = normalize(b - a);
	}

	line(const vec3& p, const plane& pl);

	vec3 p, n;
};

struct plane
{
	plane()
	{
	}

	plane(const plane& p): pl(p.pl)
	{
	}

	plane(const vec3& n, float d): pl(n, d)
	{
	}

	plane(const vec4& p): pl(p)
	{
	}

	void from_triangle(const vec3& a, const vec3& b, const vec3& c)
	{
		pl = vec4(triangle_normal(a, b, c), 1.0);
		pl = vec4(pl.xyz(), -dot(pl.xyz(), a));
	}

	void normalize()
	{
		float len = pl.normalize();
		pl.w /= len;
	}

	vec4 pl;
};

inline line::line(const vec3& p, const plane& pl)
{
	this->p = p;
	this->n = normalize(pl.pl.xyz());
}

inline float distance_from_point(const line& l, const vec2& pt)
{
	float n1 = (pt.x - l.p.x) * l.n.y - (pt.y - l.p.y) * l.n.x;

	return fabsf(n1);
}

inline float distance_from_segment_to_point(const vec2& s, const vec2 &e, const vec2& pt)
{
	vec2 dir = e - s;

	float length = dir.normalize();

	float f = dot(pt - s, dir);

	if(f < 0.0f)
		return (pt - s).length();

	if(f > length)
		return (pt - e).length();

	float n1 = (pt.x - s.x) * dir.y - (pt.y - s.y) * dir.x;

	return fabsf(n1);
}

inline float distance_from_point(const line& l, const vec3& pt)
{
	float n1 = (pt.x - l.p.x) * l.n.y - (pt.y - l.p.y) * l.n.x;
	float n2 = (pt.y - l.p.y) * l.n.z - (pt.z - l.p.z) * l.n.y;
	float n3 = (pt.z - l.p.z) * l.n.x - (pt.x - l.p.x) * l.n.z;

	return sqrtf(n1 * n1 + n2 * n2 + n3 * n3);
}

inline vec3 project_point_on_line(const line& l, const vec3& pt)
{
	return l.p + l.n * dot(pt - l.p, l.n);
}

inline float distance_from_line(const line& l1, const line& l2)
{
	mat3 detm(l1.p - l2.p, l1.n, l2.n);

	float det = detm.det();

	float n1 = l1.n.x * l2.n.y - l1.n.y * l2.n.x;
	float n2 = l1.n.y * l2.n.z - l1.n.z * l2.n.y;
	float n3 = l1.n.z * l2.n.x - l1.n.x * l2.n.z;
	float zn = sqrtf(n1 * n1 + n2 * n2 + n3 * n3);

	return det / zn;
}

inline bool line_intersects_line_2d(float s0x, float s0y, float t0x, float t0y, float s1x, float s1y, float t1x, float t1y)
{
	float v0x = t0x - s0x;
	float v0y = t0y - s0y;

	float v1x = t1x - s1x;
	float v1y = t1y - s1y;

	float d = v1x * v0y - v0x * v1y;

	float s = ((s0x - s1x) * v0y - (s0y - s1y) * v0x) / d;

	if(s < 0.0f || s > 1.0f)
		return false;

	float t = -(-(s0x - s1x) * v1y + (s0y - s1y) * v1x) / d;

	if(t < 0.0f || t > 1.0f)
		return false;

	return true;
}

inline bool line_intersects_line_2d(float s0x, float s0y, float t0x, float t0y, float s1x, float s1y, float t1x, float t1y, float &s, float &t)
{
	float v0x = t0x - s0x;
	float v0y = t0y - s0y;

	float v1x = t1x - s1x;
	float v1y = t1y - s1y;

	float d = v1x * v0y - v0x * v1y;

	s = ((s0x - s1x) * v0y - (s0y - s1y) * v0x) / d;

	if(s < 0.0f || s > 1.0f)
		return false;

	t = -(-(s0x - s1x) * v1y + (s0y - s1y) * v1x) / d;

	if(t < 0.0f || t > 1.0f)
		return false;

	return true;
}

// Returns false if parallel or if on plane
inline bool	intersect_plane(const line& l, const plane& p, vec3& pt)
{
	float a = dot(l.p, p.pl);
	float b = dot(p.pl.xyz(), l.n);

	if(fabsf(b) < Epsilon())
		return false;

	float phi = a / b;
	pt = vec3(l.p.x - l.n.x * phi, l.p.y - l.n.y * phi, l.p.z - l.n.z * phi);

	return true;
}

inline float cos_of_angle_between_lines(const line& l1, const line& l2)
{
	vec3 l1xyz = l1.n;
	vec3 l2xyz = l2.n;

	return dot(l1xyz, l2xyz);
}

inline float angle_between_lines(const line& l1, const line& l2)
{
	return acosf(cos_of_angle_between_lines(l1, l2));
}

inline float cos_of_angle_between_line_and_plane(const line& l, const plane& p)
{
	vec3 lxyz = l.n;
	vec3 pxyz = p.pl.xyz();
	return dot(lxyz, pxyz) / sqrtf(dot(pxyz, pxyz) * dot(lxyz, lxyz));
}

// Returns false if parallel or if there is no intersection in one point
inline bool	intersection_of_three_planes(const plane& p1, const plane& p2, const plane& p3, vec3& pt)
{
	mat3 d1, dx, dy, dz;
	d1 = mat3(p1.pl.xyz(), p2.pl.xyz(), p3.pl.xyz());

	float dd = d1.det();

	if(fabsf(dd) < Epsilon())
		return false;

	dx = mat3(vec3(p1.pl.w, p2.pl.w, p3.pl.w), vec3(p1.pl.y, p2.pl.y, p3.pl.y), vec3(p1.pl.z, p2.pl.z, p3.pl.z));
	dy = mat3(vec3(p1.pl.x, p2.pl.x, p3.pl.x), vec3(p1.pl.w, p2.pl.w, p3.pl.w), vec3(p1.pl.z, p2.pl.z, p3.pl.z));
	dz = mat3(vec3(p1.pl.x, p2.pl.x, p3.pl.x), vec3(p1.pl.y, p2.pl.y, p3.pl.y), vec3(p1.pl.w, p2.pl.w, p3.pl.w));
	pt = vec3(-dx.det() / dd, -dy.det() / dd, -dz.det() / dd);

	return true;
}

inline float cos_of_angle_between_planes(const plane& p1, const plane& p2)
{
	vec3 p1xyz = p1.pl.xyz();
	vec3 p2xyz = p2.pl.xyz();

	return dot(p1xyz, p2xyz) / sqrtf(dot(p1xyz, p1xyz) * dot(p2xyz, p2xyz));
}

inline float angle_between_planes(const plane& p1, const plane& p2)
{
	return acosf(cos_of_angle_between_planes(p1, p2));
}

// Returns furthest distance to the intersection of aabb planes or a negative value if there is no intersection
inline float line_intersects_aabb(const line& l, const aabb& box)
{
	vec3 min = box.min_point();
	vec3 max = box.max_point();

	float dist = -1.0f;

	vec3 intersection;

	if(intersect_plane(l, plane(vec4(1, 0, 0, -min.x)), intersection))
	{
		if(intersection.y > min.y && intersection.y < max.y && intersection.z > min.z && intersection.z < max.z)
		{
			float length = (l.p - intersection).length();

			if(length > dist)
				dist = length;
		}
	}

	if(intersect_plane(l, plane(vec4(0, 1, 0, -min.y)), intersection))
	{
		if(intersection.x > min.x && intersection.x < max.x && intersection.z > min.z && intersection.z < max.z)
		{
			float length = (l.p - intersection).length();

			if(length > dist)
				dist = length;
		}
	}

	if(intersect_plane(l, plane(vec4(0, 0, 1, -min.z)), intersection))
	{
		if(intersection.x > min.x && intersection.x < max.x && intersection.y > min.y && intersection.y < max.y)
		{
			float length = (l.p - intersection).length();

			if(length > dist)
				dist = length;
		}
	}

	if(intersect_plane(l, plane(vec4(1, 0, 0, -max.x)), intersection))
	{
		if(intersection.y > min.y && intersection.y < max.y && intersection.z > min.z && intersection.z < max.z)
		{
			float length = (l.p - intersection).length();

			if(length > dist)
				dist = length;
		}
	}

	if(intersect_plane(l, plane(vec4(0, 1, 0, -max.y)), intersection))
	{
		if(intersection.x > min.x && intersection.x < max.x && intersection.z > min.z && intersection.z < max.z)
		{
			float length = (l.p - intersection).length();

			if(length > dist)
				dist = length;
		}
	}

	if(intersect_plane(l, plane(vec4(0, 0, 1, -max.z)), intersection))
	{
		if(intersection.x > min.x && intersection.x < max.x && intersection.y > min.y && intersection.y < max.y)
		{
			float length = (l.p - intersection).length();

			if(length > dist)
				dist = length;
		}
	}

	return dist;
}

inline float line_intersect_triangle_distance(const line& l, const vec3& a, const vec3& b, const vec3& c)
{
	// http://en.wikipedia.org/wiki/Moller–Trumbore_intersection_algorithm
	vec3 e1, e2;
	vec3 p, q, t;
	float det, invDet, u, v;

	// Find vectors for two edges sharing V1
	e1 = b - a;
	e2 = c - a;

	// Begin calculating determinant - also used to calculate u parameter
	p = cross(l.n, e2);

	// If determinant is near zero, ray lies in plane of triangle
	det = dot(e1, p);

	if(det > -Epsilon() && det < Epsilon())
		return -1.0f;

	invDet = 1.0f / det;

	// Calculate distance from V1 to ray origin
	t = l.p - a;

	// Calculate u parameter and test bound
	u = dot(t, p) * invDet;

	// The intersection lies outside of the triangle
	if(u < 0.0f || u > 1.0f)
		return -1.0f;

	// Prepare to test v parameter
	q = cross(t, e1);

	// Calculate V parameter and test bound
	v = dot(l.n, q) * invDet;

	// The intersection lies outside of the triangle
	if(v < 0.0f || u + v > 1.0f)
		return -1.0f;

	float distance = dot(e2, q) * invDet;

	if(distance > Epsilon())
		return distance;

	return -1.0f;
}

inline bool line_intersects_triangle(const line& l, const vec3& a, const vec3& b, const vec3& c)
{
	return line_intersect_triangle_distance(l, a, b, c) >= 0.0f;
}

inline bool line_intersects_triangle(const line& l, const vec2& a, const vec2& b, const vec2& c)
{
	float dx = l.p.x - a.x;
	float dy = l.p.y - a.y;

	bool sign = (b.x - a.x) * dy - (b.y - a.y) * dx > 0;

	if((c.x - a.x) * dy - (c.y - a.y) * dx > 0 == sign)
		return false;

	if((c.x - b.x) * (l.p.y - b.y) - (c.y - b.y) * (l.p.x - b.x) > 0 != sign)
		return false;

	return true;
}

inline line unproject_ray(const mat4& m, vec2 point)
{
	mat4 mi = m.inverse();

	vec3 ptMin(point.x * 2.0f - 1.0f, point.y * 2.0f - 1.0f, 0.0);
	vec3 ptMax(point.x * 2.0f - 1.0f, point.y * 2.0f - 1.0f, 1.0);

	ptMin = mi * ptMin;
	ptMax = mi * ptMax;

	return line(ptMin, ptMax);
}

#undef Epsilon
