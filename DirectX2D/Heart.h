#pragma once
#include<d3d9.h>
#include<d3dx9.h>
#include<tchar.h>
#include"ScriptAble.h"

enum HeartState
{
	empty, half, full
};
class Heart : ScriptAble
{
private:
	LPDIRECT3DDEVICE9 D3Ddevice;

	LPDIRECT3DTEXTURE9 emptyTexture;
	D3DXIMAGE_INFO emptyImageInfo;

	LPDIRECT3DTEXTURE9 halfTexture;
	D3DXIMAGE_INFO halfImageInfo;

	LPDIRECT3DTEXTURE9 fullTexture;
	D3DXIMAGE_INFO fullImageInfo;

	HeartState heartState;
public:
	Heart();

	void Initialize(D3DXVECTOR2 pos);
	void Frame();
	void Release();
	
	void OnColiderEnter(ScriptAble* colObjScrt);

	void ChangeHeartState();
};