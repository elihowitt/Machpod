//#include<iostream>
//#include<string>
//#include<algorithm>
//#include<ctime>
//#include "olcConsoleGameEngine.h"
//
//using namespace std;
//
//#define PI 3.141592653589793238462643383279502884197
//
//class Projector : public olcConsoleGameEngine
//{
//public:
//	Projector()
//	{
//		m_sAppName = L'Projector';
//	}
//private:
//	enum AXIS { AXIS_X = 0, AXIS_Y = 1, AXIS_Z = 2 };
//
//	struct sCoord
//	{
//		float x;
//		float y;
//		float z;
//		sCoord(float a = 0, float b = 0, float c = 0)
//		{
//			x = a;
//			y = b;
//			z = c;
//		}
//	};
//	void DrawLineCoord(sCoord A, sCoord B, sCoord Del = { 0,0,0 }, wchar_t c = PIXEL_SOLID, COLOUR d = FG_WHITE)
//	{
//		DrawLine(A.x + Del.x, A.y + Del.y, B.x + Del.x, B.y + Del.y, c, d);
//	}
//
//	struct sTriangle
//	{
//		sCoord arrPoints[3];
//		sTriangle(sCoord A = sCoord(-1, 0, 0), sCoord B = sCoord(0, 1, 0), sCoord C = sCoord(1, 0, 0))
//		{
//			arrPoints[0] = A;
//			arrPoints[1] = B;
//			arrPoints[2] = C;
//		}
//	};
//	struct sObject
//	{
//		vector<sTriangle> vecTri;
//		sCoord centerCoord;
//		bool bActive;
//		bool bStable;
//		sObject(sCoord c = sCoord(0, 0, 0), bool ac = true, bool as = true)
//		{
//			centerCoord = c;
//			bActive = ac;
//			bStable = as;
//		}
//		void Translate(sCoord t)
//		{
//			centerCoord.x += t.x;
//			centerCoord.y += t.y;
//			centerCoord.z += t.z;
//		}
//
//		void Scale(sCoord s)
//		{
//			for (auto &tri : vecTri)
//				for (int i = 0; i < 3; i++)
//				{
//					tri.arrPoints[i].x *= s.x;
//					tri.arrPoints[i].y *= s.y;
//					tri.arrPoints[i].z *= s.z;
//				}
//		}
//		void Rotate(AXIS axi, float angle)
//		{
//			switch (axi)
//			{
//			case AXIS_X:
//				for (auto &tri : vecTri)
//					for (int i = 0; i < 3; i++)
//					{
//						///x Does not change.
//						float tmpY = tri.arrPoints[i].y;
//						tri.arrPoints[i].y = tmpY * (cos(angle)) + tri.arrPoints[i].z*(sin(angle));
//						tri.arrPoints[i].z = tmpY * (-sin(angle)) + tri.arrPoints[i].z*(cos(angle));
//					}
//				break;
//			case AXIS_Y:
//				for (auto &tri : vecTri)
//					for (int i = 0; i < 3; i++)
//					{
//						///y Does not change.
//						float tmpZ = tri.arrPoints[i].z;
//						tri.arrPoints[i].z = tmpZ * (cos(angle)) - tri.arrPoints[i].x*(sin(angle));
//						tri.arrPoints[i].x = tmpZ * (sin(angle)) + tri.arrPoints[i].x*(cos(angle));
//					}
//				break;
//			case AXIS_Z:
//				for (auto &tri : vecTri)
//					for (int i = 0; i < 3; i++)
//					{
//						///z Does not change.
//						float tmpX = tri.arrPoints[i].x;
//						tri.arrPoints[i].x = tmpX * (cos(angle)) - tri.arrPoints[i].y*(sin(angle));
//						tri.arrPoints[i].y = tmpX * (sin(angle)) + tri.arrPoints[i].y*(cos(angle));
//					}
//				break;
//			}
//		}
//	};
//
//	sCoord worldCoord;
//
//	vector<sObject*> vecObj;
//
//
//	///POINT mousePressed, mouseHeld;
//protected:
//	virtual bool OnUserCreate()
//	{
//		sObject* objSphere = new sObject;
//		make_Sphere(objSphere->centerCoord, 100, *objSphere);
//		vecObj.push_back(objSphere);
//
//		return true;
//	}
//
//	virtual bool OnUserUpdate(float fElapseTime)
//	{
//		Fill(0, 0, m_nScreenWidth, m_nScreenHeight, PIXEL_SOLID, FG_BLACK);
//
//		for (sObject *obj : vecObj)
//		{
//
//			if (GetKey(L'R').bHeld || GetKey(L'S').bHeld)
//			{
//				if (GetKey(L'R').bHeld)
//				{
//					if (GetKey(VK_UP).bHeld)
//						obj->Rotate(AXIS_X, 5 * fElapseTime);
//					else if (GetKey(VK_DOWN).bHeld)
//						obj->Rotate(AXIS_X, -5 * fElapseTime);
//					if (GetKey(VK_LEFT).bHeld)
//						obj->Rotate(AXIS_Y, 5 * fElapseTime);
//					else if (GetKey(VK_RIGHT).bHeld)
//						obj->Rotate(AXIS_Y, -5 * fElapseTime);
//					if (GetKey(L'Z').bHeld)
//						obj->Rotate(AXIS_Z, 5 * fElapseTime);
//					else if (GetKey(L'X').bHeld)
//						obj->Rotate(AXIS_Z, -5 * fElapseTime);
//				}
//				if (GetKey(L'S').bHeld)
//				{
//					if (GetKey(VK_SHIFT).bHeld)
//					{
//						if (GetKey(VK_UP).bHeld)
//							obj->Scale({ 1.0f, 1.05f, 1.0f });
//						else if (GetKey(VK_DOWN).bHeld)
//							obj->Scale({ 1.0f, 0.95f, 1.0f });
//						if (GetKey(VK_LEFT).bHeld)
//							obj->Scale({ 1.05f, 1.0f, 1.0f });
//						else if (GetKey(VK_RIGHT).bHeld)
//							obj->Scale({ 0.95f, 1.0f, 1.0f });
//						if (GetKey(L'Z').bHeld)
//							obj->Scale({ 1.0f, 1.0f, 1.05f });
//						else if (GetKey(L'X').bHeld)
//							obj->Scale({ 1.0f, 1.0f, 0.95f });
//					}
//					else
//					{
//						if (GetKey(VK_UP).bHeld)
//							obj->Scale({ 1.05f, 1.05f, 1.05f });
//						else if (GetKey(VK_DOWN).bHeld)
//							obj->Scale({ 0.95f, 0.95f, 0.95f });
//					}
//				}
//			}
//			else
//			{
//				if (GetKey(VK_UP).bHeld)
//					obj->Translate({ 0, -30 * fElapseTime, 0 });
//				else if (GetKey(VK_DOWN).bHeld)
//					obj->Translate({ 0,  30 * fElapseTime, 0 });
//				if (GetKey(VK_LEFT).bHeld)
//					obj->Translate({ -30 * fElapseTime, 0, 0 });
//				else if (GetKey(VK_RIGHT).bHeld)
//					obj->Translate({ 30 * fElapseTime, 0, 0 });
//			}
//			ConnectObject(*obj);
//		}
//
//
//
//
//
//		return true;
//	}
//
//
//
//	void CoordDelta(sCoord A, sCoord B, sCoord& tar)
//	{
//		tar.x = A.x + B.x;
//		tar.y = A.y + B.y;
//		tar.z = A.z + B.z;
//	}
//
//	void ConnectObject(sObject obj)
//	{
//		sCoord del;
//		CoordDelta(worldCoord, obj.centerCoord, del);
//		for (auto &tri : obj.vecTri)
//		{
//			for (int i = 0; i < 3; i++)
//				DrawLineCoord(tri.arrPoints[i], tri.arrPoints[(i + 1) % 3], del);
//		}
//	}
//	void make_Sphere(sCoord center, double r, sObject &obj)
//	{
//		vector<vector<sCoord>> vecVecC;
//		vector<sCoord> vecC;
//		// Iterate through phi, theta then convert r,theta,phi to  XYZ
//		for (double phi = 0., i = 0; phi < 2 * PI; phi += PI / 5., i++) // Azimuth [0, 2PI]
//		{
//			vecC.clear();
//			for (double theta = 0.; theta < PI; theta += PI / 10.) // Elevation [0, PI]
//			{
//				sCoord point;
//				point.x = r * cos(phi) * sin(theta) + center.x;
//				point.y = r * sin(phi) * sin(theta) + center.y;
//				point.z = r * cos(theta) + center.z;
//
//
//				vecC.push_back(point);
//			}
//			vecVecC.push_back(vecC);
//		}
//		obj.vecTri.push_back({ vecVecC[vecVecC.size()-1][0], vecVecC[0][0], vecVecC[0][1] });
//		for (int j = 0; j < vecVecC.size(); j++)
//		{
//			obj.vecTri.push_back({ vecVecC[j][0], vecVecC[(j + 1) % vecVecC.size()][0], vecVecC[(j + 1) % vecVecC.size()][1] });
//			for (int i = 1; i < vecC.size(); i++)
//			{
//				
//				obj.vecTri.push_back({vecVecC[j][i], vecVecC[(j+1)%vecVecC.size()][i-1], vecVecC[(j + 1) % vecVecC.size()][(i+1)%vecVecC[j].size()]});
//			}
//		}
//	}
//};
//
//int main()
//{
//	srand(time(0));
//	Projector game;
//	game.ConstructConsole(480, 320, 2, 2);//(720, 480, 2, 2);//(180, 120, 8, 8);
//	game.Start();
//	return 0;
//}