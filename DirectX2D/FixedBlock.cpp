#include"FixedBlock.h"
#include"GameObject.h"
#include"SceneManagement.h"

FixedBlock::FixedBlock()
{
	attachedObject = nullptr;
}

void FixedBlock::Initialize()
{

}
void FixedBlock::Frame()
{

}
void FixedBlock::Release()
{
	ScriptAble::Release();
}

void FixedBlock::InitBlock(LPCWSTR fileAdress, D3DXVECTOR2 pos)
{
	attachedObject = new GameObject();
	attachedObject->Initialize(fileAdress, 1, this, 0);
	attachedObject->SetColiderState(true);

	SceneManagement::GetInst()->AddScriptInScene(this);
	SceneManagement::GetInst()->AddObjectInScene(attachedObject);
	attachedObject->Teleport(pos.x, pos.y);
}
void FixedBlock::OnColiderEnter(ScriptAble* colObjScrt)
{
	GameObject* colObj = colObjScrt->GetGameObject();
	if (colObj->GetColTag() == 2)
	{
		colObj->SetActiveState(false);
	}
}