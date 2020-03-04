#include"FloatingBlock.h"
#include"GameObject.h"
#include"SceneManagement.h"

FloatingBlock::FloatingBlock()
{
	attachedObject = nullptr;
}

void FloatingBlock::Initialize()
{

}
void FloatingBlock::Frame()
{

}
void FloatingBlock::Release()
{
	ScriptAble::Release();
}

void FloatingBlock::InitBlock(LPCWSTR fileAdress, D3DXVECTOR2 pos)
{
	attachedObject = new GameObject();
	attachedObject->Initialize(fileAdress, 1, this, 0);

	SceneManagement::GetInst()->AddScriptInScene(this);
	SceneManagement::GetInst()->AddObjectInScene(attachedObject);
	attachedObject->Teleport(pos.x, pos.y);
}
void FloatingBlock::OnColiderEnter(ScriptAble* colObjScrt)
{
	GameObject* colObj = colObjScrt->GetGameObject();
	if (colObj->GetColTag() == 2)
	{
		colObj->SetActiveState(false);
	}
}