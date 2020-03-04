#include"Snowball.h"
#include"GameObject.h"
#include"SceneManagement.h"

Snowball::Snowball()
{
	attachedObject = nullptr;
	fireDir = 0;
}

void Snowball::Initialize()
{
	attachedObject = new GameObject();
	attachedObject->Initialize(L"Texture/Player/Snowball.png", 2, this, 2);
	attachedObject->SetActiveState(false);

	SceneManagement::GetInst()->AddScriptInScene(this);
	SceneManagement::GetInst()->AddObjectInScene(attachedObject);
}
void Snowball::Frame()
{
	attachedObject->Translate(fireDir * 30, 0);
}
void Snowball::Release()
{

}

void Snowball::OnColiderEnter(ScriptAble* colObjScrt)
{

}

void Snowball::FireSnow(float dir, D3DXVECTOR2 pos)
{
	attachedObject->SetActiveState(true);
	fireDir = dir;
	attachedObject->Teleport(pos.x, pos.y);
}