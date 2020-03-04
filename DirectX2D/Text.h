#pragma once
#include<d3d9.h>
#include<d3dx9.h>

class Text
{
private:
	static Text* Inst;

	ID3DXFont* font;
	int maxX;
	int maxY;
	Text();
public:
	~Text();
	void Init(int screenHeight, int screenWidth);
	void Print(LPCWSTR str, int posX, int posY, D3DXCOLOR rgb = 0xFFFFFFFF);
	static Text* GetInst();
};