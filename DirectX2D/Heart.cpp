#include"Heart.h"
#include"D3D.h"
#include"GameObject.h"
#include"SceneManagement.h"

Heart::Heart()
{
	emptyTexture = nullptr;
	halfTexture = nullptr;
	fullTexture = nullptr;

	heartState = full;
}

void Heart::Initialize(D3DXVECTOR2 pos)
{
	D3Ddevice = D3D::GetInst()->GetDevice();
	//Texture Load
	D3DXCreateTextureFromFileEx(D3Ddevice, L"Texture/Player/Heart/heart_empty.png", NULL, NULL, 1, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, 0x0000001, 0x00FFFFFF, 0x000000FF, &emptyImageInfo, NULL, &emptyTexture);
	D3DXCreateTextureFromFileEx(D3Ddevice, L"Texture/Player/Heart/heart_half.png", NULL, NULL, 1, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, 0x0000001, 0x00FFFFFF, 0x000000FF, &halfImageInfo, NULL, &halfTexture);
	D3DXCreateTextureFromFileEx(D3Ddevice, L"Texture/Player/Heart/heart_full.png", NULL, NULL, 1, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, 0x0000001, 0x00FFFFFF, 0x000000FF, &fullImageInfo, NULL, &fullTexture);

	attachedObject = new GameObject();
	attachedObject->Initialize(fullTexture, fullImageInfo, 1, this, 1);
	attachedObject->SetColiderState(false);
	attachedObject->Teleport(pos.x, pos.y);

	SceneManagement::GetInst()->AddScriptInScene(this);
	SceneManagement::GetInst()->AddObjectInScene(attachedObject);
}
void Heart::Frame()
{

}
void Heart::Release()
{

}

void Heart::OnColiderEnter(ScriptAble* colObjScrt)
{

}

void Heart::ChangeHeartState()
{
	if (heartState == full)
	{
		heartState = half;
		attachedObject->ChangeTextureForAnim(halfTexture, halfImageInfo, D3DXVECTOR2(64, 64));
	}
	else if (heartState == half)
	{
		heartState = HeartState::empty;
		attachedObject->ChangeTextureForAnim(emptyTexture, emptyImageInfo, D3DXVECTOR2(64, 64));
	}
}