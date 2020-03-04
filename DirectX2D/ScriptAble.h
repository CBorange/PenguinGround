#pragma once
#include<d3d9.h>
#include<d3dx9.h>

class GameObject;
class ScriptAble
{
protected:
	GameObject* attachedObject;
public:
	ScriptAble();
	virtual void Initialize();
	virtual void Release();
	virtual void Frame();
	virtual void OnColiderEnter(ScriptAble* colObjScrt);

	GameObject* GetGameObject();
};