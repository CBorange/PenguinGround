#include"Stage.h"
#include"MapGenerator.h"
#include"PlayerCntrl.h"

Stage::Stage()
{
	mapGenerator = nullptr;
}

void Stage::Initialize()
{
	mapGenerator = new MapGenerator();
	mapGenerator->Initialize();

	P1_Cntrl = new PlayerCntrl(L"1p", 0x65, VK_UP, VK_LEFT, VK_RIGHT, 250, 600, 40);
	P1_Cntrl->Initialize();
	P2_Cntrl = new PlayerCntrl(L"2p", 0x4A, 0x57, 0x41, 0x44, 1700, 600, 1500);
	P2_Cntrl->Initialize();
}
void Stage::Frame()
{
	Scene::Frame();
}
void Stage::Release()
{
	Scene::Release();
}