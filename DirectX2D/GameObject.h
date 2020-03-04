#pragma once
#include<d3d9.h>
#include<d3dx9.h>
using namespace std;

class ScriptAble;
class GameObject
{
private:
	LPDIRECT3DDEVICE9 D3Ddevice;
	LPD3DXSPRITE D3DSprite;

	D3DXIMAGE_INFO imageInfo;
	LPDIRECT3DTEXTURE9 texture;

	//State
	int layer;
	bool isActive;
	bool isRenderable;
	int colTag;
	int objectID;
	//Physics
	bool coliderIsActive;
	bool gravityIsActive;

	ScriptAble* attachedScript;

	D3DCOLOR color;
	D3DXVECTOR2 velocity;
	D3DXVECTOR3 position;
	D3DXVECTOR3 center;
	D3DXVECTOR3 scale;
	RECT rectPosition;
	RECT spriteRect;
public:
	GameObject();
	void Initialize(LPCWSTR fileAdress, int layer, ScriptAble* scrt,
		int colTag);
	void Initialize(LPDIRECT3DTEXTURE9 texture,
		D3DXIMAGE_INFO imageInfo, int layer, ScriptAble* scrt,
		int colTag);
	void Initialize(ScriptAble* scrt);
	void Render();
	void MoveWithVelocity();

	void Release();

	//Get
	bool GetActiveState();
	bool GetRenderable();
	int GetLayer() const;
	int GetColTag();
	bool GetColiderState();
	bool GetGravityState();

	D3DXVECTOR3 GetPosition();
	D3DXVECTOR2 GetScale();
	RECT GetRectPos();
	RECT GetSpriteRect();
	D3DXCOLOR GetColor();
	D3DXIMAGE_INFO GetImageInfo();
	ScriptAble* GetAttachedScript();
	//Set
	void ChangeTextureForAnim(LPDIRECT3DTEXTURE9 sheet,
		D3DXIMAGE_INFO imageInfo, D3DXVECTOR2 frameScale);
	void SetActiveState(bool state);
	void SetColiderState(bool state);
	void SetGravityState(bool state);
	void SetSpriteRect(RECT rect);
	void SetSpriteRect(int left, int top, int right, int bottom);
	void PushSpriteRectToRight(int pixel);
	void SetColor(float r, float g, float b, float a);
	void SetColor(float a);
	//Movement
	void Translate(D3DXVECTOR3 vec);
	void Translate(float x, float y);
	void Teleport(D3DXVECTOR3 vec);
	void Teleport(float x, float y);

	//Physics
	D3DXVECTOR2 GetVelocity();
	void SetVelocity(float x, float y);
	void SetVelocity(D3DXVECTOR2 vec);
	void AddVelocity(float x, float y);
	void AddVelocity(D3DXVECTOR2 vec);
};