#pragma once
#include<d3d9.h>
#include<d3dx9.h>
#include"Scene.h"

class MainCntrl;
class MainScene : public Scene
{
private:
	MainCntrl* mainCntrl;
public:
	MainScene();

	void Initialize();
	void Frame();
	void Release();
};