#pragma once
#include<d3d9.h>
#include<d3dx9.h>
#include<tchar.h>
#include"ScriptAble.h"

class GameObject;
class MainCntrl : ScriptAble
{
private:
	GameObject* titleBG;
	GameObject* howToPlayImage;

	bool pressAnyKeyBefore;
public:
	MainCntrl();
	~MainCntrl();

	void Initialize();
	void Frame();
	void Release();
};