#include"SceneManagement.h"
#include"Scene.h"
#include"GameObject.h"
#include"ScriptAble.h"
SceneManagement* SceneManagement::Inst = nullptr;

SceneManagement::SceneManagement()
{
	nowScene = nullptr;
}

SceneManagement* SceneManagement::GetInst()
{
	if (Inst == nullptr)
		Inst = new SceneManagement();
	return Inst;
}
Scene* SceneManagement::GetNowScene()
{
	return nowScene;
}
void SceneManagement::LoadScene(int index)
{
	if (nowScene != nullptr)
		nowScene->Release();

	nowScene = sceneList[index];
	nowScene->Initialize();
}
void SceneManagement::AddScene(Scene* scene)
{
	sceneList.push_back(scene);
}

void SceneManagement::AddObjectInScene(GameObject* obj)
{
	nowScene->AddObject(obj);
}
void SceneManagement::AddScriptInScene(ScriptAble* scrt)
{
	nowScene->AddScript(scrt);
}