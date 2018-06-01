#pragma once
#include "olcConsoleGameEngine.h"
#include"Terms.h"
#include"AbstractObjects.h"
#include"textureVertex.h"


using namespace term;

class Graphics :	public olcConsoleGameEngine
{
public:
	// Things like triangle rasteriezation shading ect
	Graphics();

	//Transforming into screen space
	float factorX, factorY;
	void transform(coord&);

	void DrawLineCoord(coord, coord, COLOUR, bool);

	void WireObject(obj);
	void FillObject(obj);

	//Standard mats
	mat3 matIdentity();
	mat3 matScaler(float);
	mat3 matRotator(AXIS, float);

	void FillTriangle(const coord&, const coord&, const coord&, COLOUR);
	void FillFlatBottomTriangle(const coord&, const coord&, const coord&, COLOUR);
	void FillFlatTopTriangle(const coord&, const coord&, const coord&, COLOUR);

	void DrawTriangleTex(const TexVertex& v0, const TexVertex& v1, const TexVertex& v2, const olcSprite& tex);
	void DrawFlatTopTriangleTex(const TexVertex& v0, const TexVertex& v1, const TexVertex& v2, const olcSprite& tex);
	void DrawFlatBottomTriangleTex(const TexVertex& v0, const TexVertex& v1, const TexVertex& v2, const olcSprite& tex);
	void DrawFlatTriangleTex(const TexVertex& v0, const TexVertex& v1, const TexVertex& v2, const olcSprite& tex,
		const TexVertex& dv0, const TexVertex& dv1, TexVertex& itEdge1);

	COLOUR ARR_COLOURS[15]{

		FG_DARK_BLUE       ,
		FG_DARK_GREEN      ,
		FG_DARK_CYAN       ,
		FG_DARK_RED        ,
		FG_DARK_MAGENTA    ,
		FG_DARK_YELLOW     ,
		FG_GREY            ,
		FG_DARK_GREY       ,
		FG_BLUE            ,
		FG_GREEN           ,
		FG_CYAN            ,
		FG_RED             ,
		FG_MAGENTA         ,
		FG_YELLOW          ,
		FG_WHITE
	};
	void FileToObj(obj& o, wstring ws);//, COLOUR col = FG_WHITE);

	~Graphics();
};

