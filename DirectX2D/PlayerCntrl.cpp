#include"PlayerCntrl.h"
#include"D3D.h"
#include"SceneManagement.h"
#include"GameObject.h"
#include"Text.h"
#include"InputManagement.h"
#include"TimeManagement.h"
#include"Heart.h"
#include"Snowball.h"

PlayerCntrl::PlayerCntrl(LPCWSTR playerID, int attackKey, int upKey, int leftKey, int rightKey,
	int spawnX, int spawnY, int heartPos)
{
	//Default
	D3Ddevice = nullptr;
	attachedObject = nullptr;

	idleTexture = nullptr;
	moveLeftTexture = nullptr;
	moveRightTexture = nullptr;

	okToJump = true;

	animState = Respawn;
	animOldTime = timeGetTime();
	animCurTime = timeGetTime();

	nowSpawn = true;
	spawnOldTime = timeGetTime();
	spawnCurTime = timeGetTime();

	fireOldTime = timeGetTime();
	fireCurTime = timeGetTime();

	heart = nullptr;
	hp = 10;
	nowHeart = 4;
	heartState = 0;

	moveDir = -1;
	snowBallIndex = 0;

	shieldOn = false;

	//Player별로 따로 초기화
	this->playerID = playerID;
	this->attackKey = attackKey;
	this->upKey = upKey;
	this->leftKey = leftKey;
	this->rightKey = rightKey;
	this->spawnX = spawnX;
	this->spawnY = spawnY;
	this->heartPos = heartPos;
}

void PlayerCntrl::Initialize()
{
	D3Ddevice = D3D::GetInst()->GetDevice();

	//idleTexture
	WCHAR textureAddr[40];
	lstrcpyW(textureAddr, L"Texture/Player/");
	lstrcatW(textureAddr, playerID);
	lstrcatW(textureAddr, L"/idle_");
	lstrcatW(textureAddr, playerID);
	lstrcatW(textureAddr, L".png");
	D3DXCreateTextureFromFileEx(D3Ddevice, textureAddr, NULL, NULL, 1, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, 0x0000001, 0x00FFFFFF, 0x000000FF, &idleImageInfo, NULL, &idleTexture);

	//leftTexture
	lstrcpyW(textureAddr, L"Texture/Player/");
	lstrcatW(textureAddr, playerID);
	lstrcatW(textureAddr, L"/left_");
	lstrcatW(textureAddr, playerID);
	lstrcatW(textureAddr, L".png");
	D3DXCreateTextureFromFileEx(D3Ddevice, textureAddr, NULL, NULL, 1, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, 0x0000001, 0x00FFFFFF, 0x000000FF, &moveLeftImageInfo, NULL, &moveLeftTexture);

	//rightTexture
	lstrcpyW(textureAddr, L"Texture/Player/");
	lstrcatW(textureAddr, playerID);
	lstrcatW(textureAddr, L"/right_");
	lstrcatW(textureAddr, playerID);
	lstrcatW(textureAddr, L".png");
	D3DXCreateTextureFromFileEx(D3Ddevice, textureAddr, NULL, NULL, 1, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, 0x0000001, 0x00FFFFFF, 0x000000FF, &moveRightImageInfo, NULL, &moveRightTexture);

	//spawnTexture
	lstrcpyW(textureAddr, L"Texture/Player/");
	lstrcatW(textureAddr, playerID);
	lstrcatW(textureAddr, L"/respawn_");
	lstrcatW(textureAddr, playerID);
	lstrcatW(textureAddr, L".png");
	D3DXCreateTextureFromFileEx(D3Ddevice, textureAddr, NULL, NULL, 1, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, 0x0000001, 0x00FFFFFF, 0x000000FF, &spawnImageInfo, NULL, &spawnTexture);

	attachedObject = new GameObject();
	attachedObject->Initialize(idleTexture, idleImageInfo, 1, this, 1);
	attachedObject->SetGravityState(true);
	attachedObject->Teleport(spawnX, spawnY);

	SceneManagement::GetInst()->AddScriptInScene(this);
	SceneManagement::GetInst()->AddObjectInScene(attachedObject);

	attachedObject->ChangeTextureForAnim(spawnTexture, spawnImageInfo, D3DXVECTOR2(128, 128));

	heart = new Heart[5];
	for (int i = 0; i < 5; ++i)
	{
		heart[i].Initialize(D3DXVECTOR2(heartPos + 80 * i, 100));
	}

	ballPool = new Snowball[12];
	for (int i = 0; i < 12; ++i)
	{
		ballPool[i].Initialize();
	}

	//LoseLogo
	lstrcpyW(textureAddr, L"Texture/Player/");
	lstrcatW(textureAddr, playerID);
	lstrcatW(textureAddr, L"/Lose_Logo_");
	lstrcatW(textureAddr, playerID);
	lstrcatW(textureAddr, L".png");

	gameOverPanel = new GameObject();
	gameOverPanel->Initialize(textureAddr, 2, this, 0);
	gameOverPanel->SetColiderState(false);
	gameOverPanel->SetActiveState(false);
	gameOverPanel->Teleport(960, 540);

	SceneManagement::GetInst()->AddObjectInScene(gameOverPanel);
}
void PlayerCntrl::Frame()
{
	//Input
	if (!nowSpawn)
	{
		if (InputManagement::GetInst()->GetKeyDown(attackKey))	//Numpad 5
		{
			ballPool[snowBallIndex].FireSnow(moveDir,
				D3DXVECTOR2(attachedObject->GetPosition().x + (moveDir * 95),
					attachedObject->GetPosition().y));

			snowBallIndex += 1;
			if (snowBallIndex > 11)
				snowBallIndex = 0;
		}
		if (InputManagement::GetInst()->GetKeyDown(upKey))
		{
			if (okToJump)
			{
				attachedObject->Translate(0, -5);
				attachedObject->AddVelocity(0, -30);
				okToJump = false;
			}
		}
		if (InputManagement::GetInst()->GetKey(leftKey))
		{
			moveDir = -1;
			attachedObject->SetVelocity(-10, attachedObject->GetVelocity().y);
			if (animState != MoveLeft)
			{
				animState = MoveLeft;
				attachedObject->ChangeTextureForAnim(moveLeftTexture, moveLeftImageInfo, D3DXVECTOR2(128, 128));
			}
		}
		if (InputManagement::GetInst()->GetKeyUp(leftKey))
		{
			attachedObject->SetVelocity(0, attachedObject->GetVelocity().y);
			animState = Idle;
			attachedObject->ChangeTextureForAnim(idleTexture, idleImageInfo, D3DXVECTOR2(128, 128));
		}
		if (InputManagement::GetInst()->GetKey(rightKey))
		{
			moveDir = 1;
			attachedObject->SetVelocity(10, attachedObject->GetVelocity().y);
			if (animState != MoveRight)
			{
				animState = MoveRight;
				attachedObject->ChangeTextureForAnim(moveRightTexture, moveRightImageInfo, D3DXVECTOR2(128, 128));
			}
		}
		if (InputManagement::GetInst()->GetKeyUp(rightKey))
		{
			attachedObject->SetVelocity(0, attachedObject->GetVelocity().y);
			animState = Idle;
			attachedObject->ChangeTextureForAnim(idleTexture, idleImageInfo, D3DXVECTOR2(128, 128));
		}
	}
	//Other
	if (attachedObject->GetPosition().y > 1150)
	{
		attachedObject->Teleport(960, -200);
	}
	CalcShieldTime();
	CalcSpawnTime();
	PlayAnimOnState();
}
void PlayerCntrl::CalcShieldTime()
{
	if (shieldOn)
	{
		//전체시간
		shieldCurTime = timeGetTime();
		if (shieldCurTime - shieldOldTime > 1000)
		{
			shieldOn = false;

		}
		//깜빡이
		twinkleCurTime = timeGetTime();
		if (twinkleCurTime - twinkleOldTime > 200)
		{

		}
	}
}
void PlayerCntrl::CalcSpawnTime()
{
	if (!nowSpawn)
		return;
	spawnCurTime = timeGetTime();
	if (spawnCurTime - spawnOldTime > 900)
	{
		nowSpawn = false;
		animState = Idle;
	}
}
void PlayerCntrl::PlayAnimOnState()
{
	animCurTime = timeGetTime();
	if (animCurTime - animOldTime > 150)
	{
		if (animState != Idle)
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
void PlayerCntrl::Release()
{
	ScriptAble::Release();
}
void PlayerCntrl::OnColiderEnter(ScriptAble* colObjScrt)
{
	GameObject* colObj = colObjScrt->GetGameObject();
	//수평 충돌처리
	if (attachedObject->GetRectPos().left < colObj->GetRectPos().right &&
		colObj->GetRectPos().left < attachedObject->GetRectPos().right)
	{
		if (attachedObject->GetPosition().x + 45 < colObj->GetRectPos().left)
		{
			attachedObject->Translate(-10, 0);
			attachedObject->SetVelocity(0, attachedObject->GetVelocity().y);
			return;
		}
		else if (attachedObject->GetPosition().x - 45 > colObj->GetRectPos().right)
		{
			attachedObject->Translate(10, 0);
			attachedObject->SetVelocity(0, attachedObject->GetVelocity().y);
			return;
		}
	}
	//수직 충돌처리
	if (attachedObject->GetRectPos().top < colObj->GetRectPos().bottom &&
		colObj->GetRectPos().top < attachedObject->GetRectPos().bottom)
	{
		okToJump = true;
		if (attachedObject->GetPosition().y > colObj->GetRectPos().bottom)
		{
			attachedObject->Translate(0, attachedObject->GetVelocity().y * -1);
			attachedObject->SetVelocity(attachedObject->GetVelocity().x, 0);
		}
		if (attachedObject->GetPosition().y < colObj->GetRectPos().top)
		{
			attachedObject->Translate(0, attachedObject->GetVelocity().y * -1);
			attachedObject->SetVelocity(attachedObject->GetVelocity().x, 0);
		}
	}
	if (colObjScrt->GetGameObject()->GetColTag() == 2)
	{
		if (!shieldOn)
		{
			heart[nowHeart].ChangeHeartState();
			heartState += 1;
			hp -= 1;

			shieldOn = true;
			shieldOldTime = timeGetTime();
			twinkleOldTime = timeGetTime();
		}
		if (heartState > 1)
		{
			nowHeart -= 1;
			heartState = 0;
		}
		if (hp < 1)
		{
			attachedObject->SetActiveState(false);
			gameOverPanel->SetActiveState(true);
		}
		colObj->SetActiveState(false);
	}
}