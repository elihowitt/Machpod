#include<iostream>
#include<string>
#include<algorithm>
#include<ctime>
#include "Graphics.h"

using namespace term;

class Projector : public Graphics
{
public:
	Projector()
	{
		m_sAppName = L'Projector';
	}
private:
	float l = 0.2f;
	obj cube; 
	coord trans, sc;
	
	obj teaPot;
	obj rabbit;

	obj dragon;

	vector<obj> vecObj;

protected:
	virtual bool OnUserCreate()
	{

		//FileToObj(rabbit, L"rabbit.txt");
		//vecObj.push_back(rabbit);

		cube.vecCoords = {
			
		{-l,-l,-l},  // 0
		{l,-l,-l },   // 1
		{-l,l,-l },   // 2
		{l,l,-l  },    // 3
		{-l,-l,l },   // 4
		{l,-l,l  },    // 5
		{-l,l,l  },    // 6
		{l,l,l   }    // 7

		};
		cube.vecTri =
		{
			{ cube.vecCoords[0], cube.vecCoords[2] , cube.vecCoords[1], ARR_COLOURS[4] },
			{ cube.vecCoords[2], cube.vecCoords[3] , cube.vecCoords[1], ARR_COLOURS[0]},
																	  	
			{ cube.vecCoords[1], cube.vecCoords[3] , cube.vecCoords[5], ARR_COLOURS[4]},
			{ cube.vecCoords[3], cube.vecCoords[7] , cube.vecCoords[5], ARR_COLOURS[0]},
																	  	
			{ cube.vecCoords[2], cube.vecCoords[6] , cube.vecCoords[3], ARR_COLOURS[3]},
			{ cube.vecCoords[3], cube.vecCoords[6] , cube.vecCoords[7], ARR_COLOURS[12]},
																	 	
			{ cube.vecCoords[4], cube.vecCoords[5] , cube.vecCoords[7], ARR_COLOURS[3]},
			{ cube.vecCoords[4], cube.vecCoords[7] , cube.vecCoords[6], ARR_COLOURS[12]},

			{ cube.vecCoords[0], cube.vecCoords[4] , cube.vecCoords[2], ARR_COLOURS[12]},
			{ cube.vecCoords[2], cube.vecCoords[4] , cube.vecCoords[6], ARR_COLOURS[4]},
																	  	
			{ cube.vecCoords[0], cube.vecCoords[1] , cube.vecCoords[4], ARR_COLOURS[15]},
			{ cube.vecCoords[1], cube.vecCoords[5] , cube.vecCoords[4], ARR_COLOURS[4]},
		};
		//Bobn
		vecObj.push_back(cube);

		return true;
	}

	virtual bool OnUserUpdate(float fElapseTime)
	{
		Fill(0, 0, m_nScreenWidth, m_nScreenHeight, PIXEL_SOLID, FG_BLACK);

		for (auto &o : vecObj)
		{

			if (GetKey(L'R').bHeld)
			{
				if (GetKey(VK_UP).bHeld)
					o.rx += o.rs*fElapseTime;
				else if (GetKey(VK_DOWN).bHeld)
					o.rx -= o.rs*fElapseTime;
				if (GetKey(VK_LEFT).bHeld)
					o.ry += o.rs*fElapseTime;
				else if (GetKey(VK_RIGHT).bHeld)
					o.ry -= o.rs*fElapseTime;
				if (GetKey(L'Z').bHeld)
					o.rz += o.rs*fElapseTime;
				else if (GetKey(L'X').bHeld)
					o.rz -= o.rs*fElapseTime;
			}
			FillObject(o);
			//WireObject(o);
		}

		
		return true;
	}

};

int main()
{


	srand(time(0));
	Projector game;
	game.ConstructConsole(WIDTH, HEIGHT, FONW, FONH);//(720, 480, 2, 2);//(180, 120, 8, 8);
	game.Start();
	return 0;
}