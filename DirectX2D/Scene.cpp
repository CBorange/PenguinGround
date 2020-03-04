#include"Scene.h"
#include"GameObject.h"
#include"ScriptAble.h"
#include"LayerSort.h"
#include"TimeManagement.h"

Scene::Scene()
{

}

void Scene::Initialize()
{

}
void Scene::Frame()
{
	CheckColiderInScene();
	ProcGameObject();
	FrameInScene();
}
void Scene::Release()
{
	ReleaseScriptInScene();
}
void Scene::ProcGameObject()
{
	list<GameObject*>::iterator iter = objectListInScene.begin();
	for (iter; iter != objectListInScene.end(); ++iter)
	{
		if ((*iter)->GetActiveState())
		{
			//Render
			if ((*iter)->GetRenderable())
				(*iter)->Render();
			//Physics
			if ((*iter)->GetGravityState())
				(*iter)->AddVelocity(0, 1);
			(*iter)->MoveWithVelocity();
		}
	}
}
void Scene::FrameInScene()
{
	list<ScriptAble*>::iterator iter = scriptListInScene.begin();
	for (iter; iter != scriptListInScene.end(); ++iter)
	{
		if ((*iter)->GetGameObject()->GetActiveState())
			(*iter)->Frame();
	}
}
void Scene::CheckColiderInScene()
{
	GameObject* nowCheckObject = nullptr;
	list<GameObject*> leftCheckObjectList = objectListInScene;

	for (int objectCount = 0; objectCount < objectListInScene.size(); ++objectCount)
	{
		nowCheckObject = leftCheckObjectList.front();
		leftCheckObjectList.pop_front();

		if (!nowCheckObject->GetActiveState() || !nowCheckObject->GetColiderState())
		{
			leftCheckObjectList.push_back(nowCheckObject);
			continue;
		}

		list<GameObject*>::iterator leftIter = leftCheckObjectList.begin();
		for (leftIter; leftIter != leftCheckObjectList.end(); ++leftIter)
		{
			if ((*leftIter)->GetActiveState() == false || (*leftIter)->GetColiderState() == false)
				continue;
			if (nowCheckObject->GetRectPos().left < (*leftIter)->GetRectPos().right &&
				nowCheckObject->GetRectPos().right >(*leftIter)->GetRectPos().left &&
				nowCheckObject->GetRectPos().top < (*leftIter)->GetRectPos().bottom &&
				nowCheckObject->GetRectPos().bottom >(*leftIter)->GetRectPos().top)
			{
				//Call EventTrigger
				nowCheckObject->GetAttachedScript()->OnColiderEnter((*leftIter)->GetAttachedScript());
				(*leftIter)->GetAttachedScript()->OnColiderEnter(nowCheckObject->GetAttachedScript());
			}
		}
		leftCheckObjectList.push_back(nowCheckObject);
	}
}
void Scene::ReleaseScriptInScene()
{
	list<ScriptAble*>::iterator iter = scriptListInScene.begin();
	for (iter; iter != scriptListInScene.end(); ++iter)
	{
		(*iter)->Release();
	}
}

void Scene::AddObject(GameObject* obj)
{
	objectListInScene.push_back(obj);
	objectListInScene.sort(LayerSort());
}
void Scene::AddScript(ScriptAble* script)
{
	scriptListInScene.push_back(script);
}