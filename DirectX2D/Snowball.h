#pragma once
#include<d3d9.h>
#include<d3dx9.h>
#include<tchar.h>
#include"ScriptAble.h"

class Snowball : ScriptAble
{
private:
	float fireDir;
public:
	Snowball();

	void Initialize();
	void Frame();
	void Release();

	void OnColiderEnter(ScriptAble* colObjScrt);

	void FireSnow(float dir, D3DXVECTOR2 pos);
};