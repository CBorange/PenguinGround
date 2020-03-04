#include"PlayerAnim.h"
#include"D3D.h"
#include"GameObject.h"
#include"SceneManagement.h"

PlayerAnim::PlayerAnim()
{
	animOldTime = timeGetTime();
	animCurTime = timeGetTime();

	animState = idle;
}

void PlayerAnim::Initialize(GameObject* attachedObject)
{
	D3Ddevice = D3D::GetInst()->GetDevice();
	//Texture Load
	D3DXCreateTextureFromFileEx(D3Ddevice, L"Texture/Player/1p/idle_1p.png", NULL, NULL, 1, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, 0x0000001, 0x00FFFFFF, 0x000000FF, &idleImageInfo, NULL, &idleTexture);
	D3DXCreateTextureFromFileEx(D3Ddevice, L"Texture/Player/1p/left_1p.png", NULL, NULL, 1, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, 0x0000001, 0x00FFFFFF, 0x000000FF, &moveLeftImageInfo, NULL, &moveLeftTexture);
	D3DXCreateTextureFromFileEx(D3Ddevice, L"Texture/Player/1p/right_1p.png", NULL, NULL, 1, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, 0x0000001, 0x00FFFFFF, 0x000000FF, &moveRightImageInfo, NULL, &moveRightTexture);
	D3DXCreateTextureFromFileEx(D3Ddevice, L"Texture/Player/1p/respawn_1p.png", NULL, NULL, 1, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, 0x0000001, 0x00FFFFFF, 0x000000FF, &spawnImageInfo, NULL, &spawnTexture);

	this->attachedObject = attachedObject;

	SceneManagement::GetInst()->AddObjectInScene(attachedObject);
	SceneManagement::GetInst()->AddScriptInScene(this);
}
void PlayerAnim::Frame()
{

}
void PlayerAnim::Release()
{

}

//PlayerAnim
void PlayerAnim::PlayAnimOnState()
{
	animCurTime = timeGetTime();
	if (animCurTime - animOldTime > 150)
	{
		if (animState != idle)
		{
			attachedObject->PushSpriteRectToRight(128);
			if (attachedObject->GetSpriteRect().left > attachedObject->GetImageInfo().Width - 128)
			{
				attachedObject->SetSpriteRect(0, 0, 128, 128);
			}
			animOldTime = animCurTime;
		}
	}
}
void PlayerAnim::ChangeAnimToSpawn()
{
	attachedObject->ChangeTextureForAnim(spawnTexture, spawnImageInfo, D3DXVECTOR2(128, 128));
}
void PlayerAnim::ChangeAnimToIdle()
{
	animState = idle;
	attachedObject->ChangeTextureForAnim(idleTexture, idleImageInfo, D3DXVECTOR2(128, 128));

}
void PlayerAnim::ChangeAnimToMoveLeft()
{
	if (animState != moveLeft)
	{
		animState = moveLeft;
		attachedObject->ChangeTextureForAnim(moveLeftTexture, moveLeftImageInfo, D3DXVECTOR2(128, 128));
	}
}
void PlayerAnim::ChangeAnimToMoveRight()
{
	if (animState != moveRight)
	{
		animState = moveRight;
		attachedObject->ChangeTextureForAnim(moveRightTexture, moveRightImageInfo, D3DXVECTOR2(128, 128));
	}
}