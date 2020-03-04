#pragma once
#include<d3d9.h>
#include<d3dx9.h>
#include"Scene.h"

class MapGenerator;
class PlayerCntrl;
class Stage : public Scene
{
private:
	MapGenerator* mapGenerator;
	PlayerCntrl* P1_Cntrl;
	PlayerCntrl* P2_Cntrl;
public:
	Stage();

	void Initialize();
	void Frame();
	void Release();
};