#pragma once
#include <d3d9.h>
#include<d3dx9.h>
#include <list>
using namespace std;

class GameObject;
class ScriptAble;

class Scene
{
protected:
	list<GameObject*> objectListInScene;
	list<ScriptAble*> scriptListInScene;
protected:
	void ProcGameObject();
	void FrameInScene();
	void ReleaseScriptInScene();
	//Physics
	void CheckColiderInScene();

public:
	Scene();
	virtual void Initialize();
	virtual void Frame();
	virtual void Release();

	void AddObject(GameObject* obj);
	void AddScript(ScriptAble* script);
};