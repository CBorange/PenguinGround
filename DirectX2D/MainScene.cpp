#include"MainScene.h"
#include"MainCntrl.h"

MainScene::MainScene()
{
	mainCntrl = nullptr;
}

void MainScene::Initialize()
{
	mainCntrl = new MainCntrl();
	mainCntrl->Initialize();
}
void MainScene::Frame()
{
	Scene::Frame();
}
void MainScene::Release()
{
	Scene::Release();

	delete mainCntrl;
	mainCntrl = nullptr;
}