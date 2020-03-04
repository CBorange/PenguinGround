#include"D3D.h"
#include"Scene.h"
#include"SceneManagement.h"
#include"MainScene.h"
#include"Stage.h"
#include"Text.h"

D3D* D3D::Inst = nullptr;

D3D::D3D()
{
	_D3D = nullptr;
	_D3Ddevice = nullptr;
	_D3DSprite = nullptr;

	sceneManagement = SceneManagement::GetInst();
}
D3D::~D3D()
{

}
D3D* D3D::GetInst()
{
	if (Inst == nullptr)
		Inst = new D3D();
	return Inst;
}

LPDIRECT3DDEVICE9 D3D::GetDevice()
{
	return _D3Ddevice;
}
LPD3DXSPRITE D3D::GetSprite()
{
	return _D3DSprite;
}

void D3D::Create(HWND hWnd, int& screenWidth, int& screenHeight)
{
	this->hWnd = hWnd;
	_D3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = !FULL_SCREEN;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferHeight = screenHeight;
	d3dpp.BackBufferWidth = screenWidth;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.hDeviceWindow = hWnd;

	if (FAILED(_D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &_D3Ddevice)))
	{
		if (FAILED(_D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &_D3Ddevice)))
		{
			if (FAILED(_D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
				D3DCREATE_MIXED_VERTEXPROCESSING, &d3dpp, &_D3Ddevice)))
			{
				_D3D->Release();
				_D3D = NULL;
			}
		} 
	}
	if (FAILED(D3DXCreateSprite(_D3Ddevice, &_D3DSprite)))
	{
		_D3Ddevice->Release();
		_D3Ddevice = NULL;

		_D3D->Release();
		_D3D = NULL;
	}

	//System Init
	Text::GetInst()->Init(screenHeight, screenWidth);
}
void D3D::Initialize()
{
	//ºôµåÇÒ ¾À ÀüºÎ Ãß°¡
	sceneManagement->AddScene(new MainScene());
	sceneManagement->AddScene(new Stage());

	//Ã¹¹øÂ° ¾À ·Îµå
	sceneManagement->LoadScene(0);
}
void D3D::Frame()
{
	_D3Ddevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DXCOLOR(0, 0, 1, 1), 1.0f, 0);

	_D3Ddevice->BeginScene();
	_D3DSprite->Begin(D3DXSPRITE_ALPHABLEND);

	sceneManagement->GetNowScene()->Frame();

	_D3DSprite->End();
	_D3Ddevice->EndScene();

	_D3Ddevice->Present(NULL, NULL, NULL, NULL);
}
void D3D::Release()
{
	sceneManagement->GetNowScene()->Release();

	_D3DSprite->Release();
	_D3DSprite = NULL;

	_D3Ddevice->Release();
	_D3Ddevice = NULL;

	_D3D->Release();
	_D3D = NULL;
}