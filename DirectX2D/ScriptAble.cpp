#include"ScriptAble.h"
#include"GameObject.h"

ScriptAble::ScriptAble()
{
	attachedObject = nullptr;
}

void ScriptAble::Initialize()
{

}
void ScriptAble::Release()
{
	attachedObject->Release();
	delete attachedObject;
}
void ScriptAble::Frame()
{

}
void ScriptAble::OnColiderEnter(ScriptAble* colObjScrt)
{

}

GameObject* ScriptAble::GetGameObject()
{
	return attachedObject;
}