#include<d3d9.h>
#include<d3dx9.h>

const bool FULL_SCREEN = false;
class Scene;
class SceneManagement;
class D3D
{
private:
	static D3D* Inst;

	LPDIRECT3D9         _D3D;
	LPDIRECT3DDEVICE9   _D3Ddevice;
	LPD3DXSPRITE _D3DSprite;
	HWND hWnd;

	SceneManagement* sceneManagement;
	D3D();
	~D3D();
public:
	static D3D* GetInst();

	LPDIRECT3DDEVICE9 GetDevice();
	LPD3DXSPRITE GetSprite();
	void Create(HWND hWnd, int& screenWidth, int& screenHeight);
	void Initialize();
	void Frame();
	void Release();
};