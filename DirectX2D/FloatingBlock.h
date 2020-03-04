#pragma once
#include<d3d9.h>
#include<d3dx9.h>
#include"ScriptAble.h"

class FloatingBlock : ScriptAble
{
private:

public:
	FloatingBlock();

	void Initialize();
	void Frame();
	void Release();

	void InitBlock(LPCWSTR fileAdress, D3DXVECTOR2 pos);
	void OnColiderEnter(ScriptAble* colObjScrt);
};