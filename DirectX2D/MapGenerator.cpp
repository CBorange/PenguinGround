#include"MapGenerator.h"
#include"GameObject.h"
#include"SceneManagement.h"
#include"FixedBlock.h"
#include"FloatingBlock.h"

MapGenerator::MapGenerator()
{
	fixedBlockArray = nullptr;
	floatingBlockArray = nullptr;
}
MapGenerator::~MapGenerator()
{

}

void MapGenerator::Initialize()
{
	//Default Init
	attachedObject = new GameObject();
	attachedObject->Initialize(L"Texture/Map/BG.png", 0, this, 0);
	attachedObject->Teleport(960, 540);
	attachedObject->SetColiderState(false);

	SceneManagement::GetInst()->AddObjectInScene(attachedObject);
	SceneManagement::GetInst()->AddScriptInScene(this);

	MapGenerate();
}
void MapGenerator::Frame()
{

}
void MapGenerator::Release()
{
	ScriptAble::Release();
}

//MapGenerator
void MapGenerator::MapGenerate()
{
	fixedBlockArray = new FixedBlock[5];
	floatingBlockArray = new FloatingBlock[6];

	fixedBlockArray[0].InitBlock(L"Texture/Map/left_Pillar.png", D3DXVECTOR2(40, 540));
	fixedBlockArray[1].InitBlock(L"Texture/Map/right_Pillar.png", D3DXVECTOR2(1880, 540));
	fixedBlockArray[2].InitBlock(L"Texture/Map/left_Bottom_Land.png", D3DXVECTOR2(280, 990));
	fixedBlockArray[3].InitBlock(L"Texture/Map/right_Bottom_Land.png", D3DXVECTOR2(1640, 990));
	fixedBlockArray[4].InitBlock(L"Texture/Map/middle_Middle_Land.png", D3DXVECTOR2(970, 940));

	floatingBlockArray[0].InitBlock(L"Texture/Map/left_Middle_Plate.png", D3DXVECTOR2(470, 720));
	floatingBlockArray[1].InitBlock(L"Texture/Map/right_Middle_Plate.png", D3DXVECTOR2(1450, 720));
	floatingBlockArray[2].InitBlock(L"Texture/Map/left_Top_Plate.png", D3DXVECTOR2(215, 250));
	floatingBlockArray[3].InitBlock(L"Texture/Map/right_Top_Plate.png", D3DXVECTOR2(1705, 250));
	floatingBlockArray[4].InitBlock(L"Texture/Map/middle_Top_Plate.png", D3DXVECTOR2(970, 250));
	floatingBlockArray[5].InitBlock(L"Texture/Map/middle_Middle_Plate.png", D3DXVECTOR2(970, 480));
}