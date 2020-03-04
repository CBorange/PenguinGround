#pragma once
#include<d3d9.h>
#include<d3dx9.h>
#include<vector>
using namespace std;

class GameObject;
class ScriptAble;
class Scene;
class SceneManagement
{
private:
	Scene* nowScene;
	vector<Scene*> sceneList;
	static SceneManagement* Inst;
public:
	SceneManagement();
	static SceneManagement* GetInst();
	Scene* GetNowScene();
	void LoadScene(int index);
	void AddScene(Scene* scene);

	void AddObjectInScene(GameObject* obj);
	void AddScriptInScene(ScriptAble* scrt);
};