#include "Graphics.h"



Graphics::Graphics()
{
	factorX = (float)WIDTH / 2.0f, factorY = (float)HEIGHT / 2.0f;

}

void Graphics::transform(coord &c)
{
	const float zInv = 1.0f / c.z;
	c.x = (c.x  * zInv + 1)*factorX;
	c.y = (-c.y * zInv + 1)*factorY;
}

void Graphics::DrawLineCoord(coord a, coord b, COLOUR col, bool trans = 0)
{
	if (trans)
	{
		transform(a);
		transform(b);
	}
	DrawLine(a.x, a.y, b.x, b.y, PIXEL_SOLID, col);
}

void Graphics::WireObject(obj o)
{


	mat3 rot =
		matRotator(AXIS_X, o.rx)*
		matRotator(AXIS_Y, o.ry)*
		matRotator(AXIS_Z, o.rz);

	for (auto &t : o.vecTri)
	{
		for (auto &v : t.vertices)
		{
			v *= rot;
			v += {0.0f, 0.0f, 1.0f};
			transform(v);
		}
	}
	for (auto &t : o.vecTri)
		for (int i = 0; i < 3; i++)
			DrawLineCoord(t.vertices[i], t.vertices[(i + 1) % 3], FG_RED);
}

void Graphics::FillObject(obj o)
{
	mat3 rot =
		matRotator(AXIS_X, o.rx)*
		matRotator(AXIS_Y, o.ry)*
		matRotator(AXIS_Z, o.rz);

	for (auto &t : o.vecTri)
		for (auto &v : t.vertices)
		{
			v *= rot;
			v += {0.0f, 0.0f, 1.0f};
		}
	for (auto &t : o.vecTri)
	{
		coord& v0 = t.vertices[0];
		coord& v1 = t.vertices[1];
		coord& v2 = t.vertices[2];
		t.culled = (v1 - v0) % (v2 - v0) * v0 >= 0.0f;
	}

	for (auto &t : o.vecTri)
		for (auto &v : t.vertices)
			transform(v);

	for (auto &t : o.vecTri)
		if (!t.culled)FillTriangle(t.vertices[0], t.vertices[1], t.vertices[2], t.colour);
}
//void Graphics::FillObject(obj o)
//{
//	mat3 rot =
//		matRotator(AXIS_X, o.rx)*
//		matRotator(AXIS_Y, o.ry)*
//		matRotator(AXIS_Z, o.rz);
//
//	for (auto &t : o.vecTri)
//		for (auto &v : t.vertices)
//		{
//			v *= rot;
//			v += {0.0f, 0.0f, 1.0f};
//			transform(v);
//		}			
//
//	for (auto &t : o.vecTri)
//		FillTriangle(t.vertices[0], t.vertices[1], t.vertices[2], t.colour);
//}


mat3 Graphics::matIdentity()
{
	float id[3][3]{
		{ 1.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f }
	};
	return id;
}
mat3 Graphics::matScaler(float n)
{
	float sc[3][3]{
		{ n,    0.0f, 0.0f },
	{ 0.0f, n,    0.0f },
	{ 0.0f, 0.0f, n }
	};
	return sc;
}
mat3 Graphics::matRotator(AXIS a, float t)
{
	if (a == AXIS_X)
	{
		float r[3][3]
		{
			{ 1, 0      ,        0 },
		{ 0, cosf(t), -sinf(t) },
		{ 0, sinf(t),  cosf(t) }
		};
		return r;
	}
	else if (a == AXIS_Y)
	{
		float r[3][3]
		{
			{ cosf(t) , 0      ,  sinf(t) },
		{ 0       , 1      , 0 },
		{ -sinf(t), 0      ,  cosf(t) }
		};
		return r;
	}
	else
	{
		float r[3][3]
		{
			{ cosf(t) , -sinf(t),     0 },
		{ sinf(t) , cosf(t) ,     0 },
		{ 0       , 0       ,     1 }
		};
		return r;
	}
}

void Graphics::FillTriangle(const coord& v0, const coord& v1, const coord& v2, COLOUR col)
{
	//Using pointers so we can sort vertecies
	const coord* pv0 = &v0;
	const coord* pv1 = &v1;
	const coord* pv2 = &v2;

	//Sorting by y
	if (pv1->y < pv0->y)std::swap(pv0, pv1);
	if (pv2->y < pv1->y)std::swap(pv1, pv2);
	if (pv1->y < pv0->y)std::swap(pv0, pv1);

	//If the top y's equale => flat top
	if (pv0->y == pv1->y)
	{
		//Sort by x
		if (pv1->x < pv0->x)std::swap(pv1, pv0);
		FillFlatTopTriangle(*pv0, *pv1, *pv2, col);
	}
	//If bottom two equale hight => flat bottom
	else if (pv1->y == pv2->y)
	{
		//Sort by x
		if (pv2->x < pv1->x)std::swap(pv1, pv2);
		FillFlatBottomTriangle(*pv0, *pv1, *pv2, col);
	}
	//General triangle
	else
	{
		//Find splitting vertex
		const float alphaSplit =
			(pv1->y - pv0->y) /
			(pv2->y - pv0->y);

		//A 2D coord acually but no class/energy to make one :p
		//const coord vi = *pv0 + (*pv2 - *pv0) * alphaSplit;
		coord vi;
		vi.y = pv1->y;
		vi.x = pv0->x + (pv2->x - pv0->x) * alphaSplit;

		//Majority of the side of the triangle matters cuz of order
		if (pv1->x < vi.x)//Right
		{
			FillFlatBottomTriangle(*pv0, *pv1, vi, col);
			FillFlatTopTriangle(*pv1, vi, *pv2, col);
		}
		else//Left
		{
			FillFlatBottomTriangle(*pv0, vi, *pv1, col);
			FillFlatTopTriangle(vi, *pv1, *pv2, col);
		}
	}

}

void Graphics::FillFlatTopTriangle(const coord& v0, const coord& v1, const coord& v2, COLOUR col)
{
	//We calc x/y slopes cuz there might be a vertical line but never a horizontal one.
	float m0 = (v2.x - v0.x) / (v2.y - v0.y);
	float m1 = (v2.x - v1.x) / (v2.y - v1.y);

	//Scanlines with the 'top left' rule;
	const int startY = (int)ceil(v0.y - 0.5f);
	const int endY = (int)ceil(v2.y - 0.5f);

	for (int y = startY; y < endY; y++)
	{
		const float px0 = m0 * ((float)(y)+0.5f - v0.y) + v0.x;
		const float px1 = m1 * ((float)(y)+0.5f - v1.y) + v1.x;

		const int startX = (int)ceil(px0 - 0.5f);
		const int endX = (int)ceil(px1 - 0.5f);

		for (int x = startX; x < endX; x++)
			Draw(x, y, PIXEL_SOLID, col);
	}
}
void Graphics::FillFlatBottomTriangle(const coord& v0, const coord& v1, const coord& v2, COLOUR col)
{
	//We calc x/y slopes cuz there might be a vertical line but never a horizontal one.
	float m0 = (v1.x - v0.x) / (v1.y - v0.y);
	float m1 = (v2.x - v0.x) / (v2.y - v0.y);

	//Scanlines with the 'top left' rule;
	const int startY = (int)ceil(v0.y - 0.5f);
	const int endY = (int)ceil(v2.y - 0.5f);

	for (int y = startY; y < endY; y++)
	{
		const float px0 = m0 * ((float)(y)+0.5f - v0.y) + v0.x;
		const float px1 = m1 * ((float)(y)+0.5f - v0.y) + v0.x;

		const int startX = (int)ceil(px0 - 0.5f);
		const int endX = (int)ceil(px1 - 0.5f);

		for (int x = startX; x < endX; x++)
			Draw(x, y, PIXEL_SOLID, col);
	}
}


void Graphics::FileToObj(obj& o, wstring ws)//, COLOUR col = FG_WHITE)
{
	ifstream f(ws);

	vector<coord> vecC;
	vector<tri> vecT;

	tri k;
	coord s;

	while (!f.eof())
	{

		char a;
		f.get(a);

		switch (a)
		{

		case 'v':
			f >> s.x;
			f >> s.y;
			f >> s.z;

			s.x /= 1000;
			s.y /= 1000;
			s.z /= 1000;

			vecC.push_back(s);
			break;

		case 'f':
			f >> s.x;
			f >> s.y;
			f >> s.z;

			///Take notis if the files uses array iterators or we need to subtrackt 1.
			//k = { vecC[s.x ], vecC[s.y ], vecC[s.z ], FG_BLUE };//col };
			//k = { vecC[s.x - 1], vecC[s.y - 1], vecC[s.z - 1], ARR_COLOURS[rand() % 16] };//col };
			k = { vecC[s.x - 1], vecC[s.y - 1], vecC[s.z - 1], FG_WHITE };//col };

			vecT.push_back(k);

			break;
		}

	}



	o.vecCoords = vecC;
	o.vecTri = vecT;



	f.close();
}

Graphics::~Graphics()
{
}

