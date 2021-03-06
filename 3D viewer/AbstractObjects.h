#pragma once
#include "Terms.h"
#include"olcConsoleGameEngine.h"
#include<vector>

using namespace term;

class mat3
{
public:
	mat3() {}
	mat3(float a[3][3])
	{
		for (int y = 0; y < 3; y++)
			for (int x = 0; x < 3; x++)
				vals[y][x] = a[y][x];
	}
	mat3(mat3* mat)
	{
		for (int y = 0; y < 3; y++)
			for (int x = 0; x < 3; x++)
				vals[y][x] = mat->vals[y][x];
	}

	mat3& operator=(const mat3 rhs)
	{
		memcpy(vals, rhs.vals, sizeof(vals));
		return *this;
	}
	mat3 operator*(const mat3 rhs) const
	{
		mat3 result;
		for (size_t j = 0; j < 3; j++)
		{
			for (size_t k = 0; k < 3; k++)
			{
				float sum = 0.0f;
				for (size_t i = 0; i < 3; i++)
				{
					sum += vals[j][i] * rhs.vals[i][k];
				}
				result.vals[j][k] = sum;
			}
		}
		return result;
	}



	float vals[3][3];
};

class coord
{
public:

	float x;
	float y;
	float z;

	coord(float ax = 0, float ay = 0, float az = 0)
	{
		x = ax;
		y = ay;
		z = az;
	}
	coord(float a[3])
	{
		x = a[0];
		y = a[1];
		z = a[2];
	}
	coord operator*(mat3 m)
	{
		float val[]{ x,y,z };
		float xp = 0, yp = 0, zp = 0;
		float valp[]{ xp,yp,zp };
		for (int y = 0; y < 3; y++)
			for (int x = 0; x < 3; x++)
				valp[y] += m.vals[y][x] * val[x];
		return valp;
	}
	void operator*=(mat3 m)
	{
		*this = *this * m;
	}	

	coord	operator-() const
	{
		return coord(-x, -y, -z);
	}
	coord&	operator=(const coord &rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}
	coord&	operator+=(const coord &rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}
	coord&	operator-=(const coord &rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}
	float	operator*(const coord &rhs) const
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}
	coord	operator+(const coord &rhs) const
	{
		return coord(*this) += rhs;
	}
	coord	operator-(const coord &rhs) const
	{
		return coord(*this) -= rhs;
	}
	coord&	operator*=(const float &rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		return *this;
	}
	coord	operator*(const float &rhs) const
	{
		return coord(*this) *= rhs;
	}
	coord	operator%(const coord& rhs) const
	{
		return coord(
			y * rhs.z - z * rhs.y,
			z * rhs.x - x * rhs.z,
			x * rhs.y - y * rhs.x);
	}
	coord&	operator/=(const float &rhs)
	{
		x /= rhs;
		y /= rhs;
		z /= rhs;
		return *this;
	}
	coord	operator/(const float &rhs) const
	{
		return coord(*this) /= rhs;
	}

	coord	InterpolateTo(const coord& dest, float alpha) const
	{
		return *this + (dest - *this) * alpha;
	}

	~coord() {}
};


class TexVertex
{
public:
	TexVertex(const coord& pos, const coord& tc)
		:
		pos(pos),
		tc(tc)
	{}
	TexVertex InterpolateTo(const TexVertex& dest, float alpha) const
	{
		return{
			pos.InterpolateTo(dest.pos,alpha),
			tc.InterpolateTo(dest.tc,alpha)
		};
	}
	TexVertex& operator+=(const TexVertex& rhs)
	{
		pos += rhs.pos;
		tc += rhs.tc;
		return *this;
	}
	TexVertex operator+(const TexVertex& rhs) const
	{
		return TexVertex(*this) += rhs;
	}
	TexVertex& operator-=(const TexVertex& rhs)
	{
		pos -= rhs.pos;
		tc -= rhs.tc;
		return *this;
	}
	TexVertex operator-(const TexVertex& rhs) const
	{
		return TexVertex(*this) -= rhs;
	}
	TexVertex& operator*=(float rhs)
	{
		pos *= rhs;
		tc *= rhs;
		return *this;
	}
	TexVertex operator*(float rhs) const
	{
		return TexVertex(*this) *= rhs;
	}
	TexVertex& operator/=(float rhs)
	{
		pos /= rhs;
		tc /= rhs;
		return *this;
	}
	TexVertex operator/(float rhs) const
	{
		return TexVertex(*this) /= rhs;
	}
public:
	coord pos;
	coord tc;
};

class tri
{
public:
	tri() {}
	tri(coord a, coord b, coord c, COLOUR col = FG_BLUE, bool cull = false)
	{
		vertices[0] = a;
		vertices[1] = b;
		vertices[2] = c;
		colour = col;
		culled = cull;
	}
	~tri() {}
	coord vertices[3];
	COLOUR colour;
	bool culled;
};
class obj
{
public:
	obj(float r = 5.0f, float t = 3.0f, float s = 2.0f) { rx = 0; ry = 0; rz = 0; rs = r; ts = t; ss = s; }
	obj(std::vector<coord> vecC, float r = 5.0f, float t = 3.0f, float s = 2.0f)
	{
		vecCoords = vecC; rx = 0; ry = 0; rz = 0;  rs = r; ts = t; ss = s; vecTex.clear();
	}
	obj(std::vector<coord> vecC, std::vector<tri> vecT, float r = 5.0f, float t = 3.0f, float s = 2.0f)
	{
		vecCoords = vecC; vecTri = vecT; rx = 0; ry = 0; rz = 0; rs = r; ts = t; ss = s;
	}

	std::vector<coord> vecCoords;
	std::vector<tri> vecTri;
	std::vector<TexVertex> vecTex;

	//Orientation.
	float rx, ry, rz;
	//Speeds
	float rs, ts, ss;

	~obj() {}
};
