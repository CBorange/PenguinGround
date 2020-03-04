#pragma once
#include<d3d9.h>
#include<d3dx9.h>
#include<tchar.h>
#include"ScriptAble.h"

enum AnimState
{
	idle, moveLeft, moveRight, Spawn, Win
};
class PlayerAnim : ScriptAble
{
private:
	LPDIRECT3DDEVICE9 D3Ddevice;

	LPDIRECT3DTEXTURE9 idleTexture;
	D3DXIMAGE_INFO idleImageInfo;

	LPDIRECT3DTEXTURE9 moveLeftTexture;
	D3DXIMAGE_INFO moveLeftImageInfo;

	LPDIRECT3DTEXTURE9 moveRightTexture;
	D3DXIMAGE_INFO moveRightImageInfo;

	LPDIRECT3DTEXTURE9 spawnTexture;
	D3DXIMAGE_INFO spawnImageInfo;

	AnimState animState;

	float animOldTime;
	float animCurTime;
private:
	void PlayAnimOnState();
public:
	PlayerAnim();

	void Initialize(GameObject* attachedObject);
	void Frame();
	void Release();

	//PlayerAnim
	void ChangeAnimToSpawn();
	void ChangeAnimToIdle();
	void ChangeAnimToMoveLeft();
	void ChangeAnimToMoveRight();
};