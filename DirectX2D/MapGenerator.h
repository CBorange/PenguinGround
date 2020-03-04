#pragma once
#include<d3d9.h>
#include<d3dx9.h>
#include<tchar.h>
#include"ScriptAble.h"

class FixedBlock;
class FloatingBlock;
class MapGenerator : ScriptAble
{
private:
	FixedBlock* fixedBlockArray;
	FloatingBlock* floatingBlockArray;
public:
	MapGenerator();
	~MapGenerator();

	void Initialize();
	void Frame();
	void Release();

	//MapGenerator
	void MapGenerate();
};