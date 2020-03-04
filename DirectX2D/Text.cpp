#include"Text.h"
#include"D3D.h"

//swprintf(TCHAR str,sizeof(str),����) �̷��� ���� float�� ������.

Text* Text::Inst = nullptr;

Text::Text()
{

}
Text::~Text()
{

}

void Text::Init(int screenHeight, int screenWidth)
{
	D3DXFONT_DESC fontDESC;
	ZeroMemory(&fontDESC, sizeof(D3DXFONT_DESC));

	fontDESC.Height = 15;
	fontDESC.Width = 15;
	fontDESC.Weight = FW_NORMAL;
	fontDESC.MipLevels = D3DX_DEFAULT;
	fontDESC.Italic = false;
	fontDESC.CharSet = DEFAULT_CHARSET;
	fontDESC.OutputPrecision = OUT_DEFAULT_PRECIS;
	fontDESC.Quality = DEFAULT_QUALITY;
	fontDESC.PitchAndFamily = DEFAULT_PITCH;
	fontDESC.FaceName, TEXT("�������");
	maxX = screenWidth;
	maxY = screenHeight;
	D3DXCreateFontIndirect(D3D::GetInst()->GetDevice(), &fontDESC, &font);
}
void Text::Print(LPCWSTR str, int posX, int posY, D3DXCOLOR rgb)
{
	RECT printRect = { posX,posY,maxX,maxY };
	font->DrawTextW(0, str, -1, &printRect, DT_TOP | DT_LEFT, rgb);
}

Text* Text::GetInst()
{
	if (Inst == nullptr)
		Inst = new Text();
	return Inst;
}