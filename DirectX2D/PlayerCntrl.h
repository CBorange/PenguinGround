#pragma once
#include<d3d9.h>
#include<d3dx9.h>
#include<tchar.h>
#include"ScriptAble.h"
#include<list>
using namespace std;

enum AnimState
{
	Idle, MoveLeft, MoveRight, Respawn, Win
};
class Heart;
class Snowball;
class PlayerCntrl : ScriptAble
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

	GameObject* gameOverPanel;

	AnimState animState;

	float moveDir;

	bool okToJump;
	float animOldTime;
	float animCurTime;

	float spawnOldTime;
	float spawnCurTime;
	bool nowSpawn;

	float fireOldTime;
	float fireCurTime;

	Heart* heart;
	Snowball* ballPool;
	int hp;
	int nowHeart;
	int heartState;

	int snowBallIndex;

	bool shieldOn;
	float shieldOldTime;
	float shieldCurTime;
	float twinkleOldTime;
	float twinkleCurTime;

	//Player별로 다른변수
	LPCWSTR playerID;
	int attackKey;
	int upKey;
	int leftKey;
	int rightKey;
	int spawnX;
	int spawnY;
	int heartPos;

private:
	void CalcShieldTime();
	void CalcSpawnTime();
	void PlayAnimOnState();
public:
	PlayerCntrl(LPCWSTR playerID, int attackKey, int upKey,
		int leftKey, int rightKey, int spawnX, int spawnY,
		int heartPos);
	void Initialize();
	void Frame();
	void Release();

	void OnColiderEnter(ScriptAble* colObjScrt);
};