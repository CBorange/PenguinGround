#include"MainCntrl.h"]
#include"SceneManagement.h"
#include"GameObject.h"
#include"Text.h"
#include"InputManagement.h"

MainCntrl::MainCntrl()
{
	attachedObject = nullptr;

	titleBG = nullptr;
	howToPlayImage = nullptr;

	pressAnyKeyBefore = false;
}
MainCntrl::~MainCntrl()
{

}

void MainCntrl::Initialize()
{

	attachedObject = new GameObject();
	attachedObject->Initialize(this);

	SceneManagement::GetInst()->AddScriptInScene(this);

	titleBG = new GameObject();
	titleBG->Initialize(L"Texture/MainScene/title.png", 0, this, 0);
	titleBG->Teleport(960, 540);
	titleBG->SetColiderState(false);
	SceneManagement::GetInst()->AddObjectInScene(titleBG);

	howToPlayImage = new GameObject();
	howToPlayImage->Initialize(L"Texture/MainScene/key_Window.png", 1, this, 0);
	howToPlayImage->Teleport(960, 540);
	howToPlayImage->SetColiderState(false);
	SceneManagement::GetInst()->AddObjectInScene(howToPlayImage);
	howToPlayImage->SetActiveState(false);
}
void MainCntrl::Frame()
{
	if (InputManagement::GetInst()->GetKeyDown(VK_RETURN))
	{
		Text::GetInst()->Print(L"asdf", 300, 300);
		if (!pressAnyKeyBefore)
		{
			pressAnyKeyBefore = true;
			howToPlayImage->SetActiveState(true);
			return;
		}
		SceneManagement::GetInst()->LoadScene(1);
	}
}
void MainCntrl::Release()
{
	ScriptAble::Release();


}