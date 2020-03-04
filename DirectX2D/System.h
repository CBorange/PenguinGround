#include<d3d9.h>
#include<d3dx9.h>
#include<iostream>
#include<stdio.h>
#include<tchar.h>

class D3D;
class System
{
private:
	LPCWSTR applicationName;

	D3D* D3DClass;
	HINSTANCE hInst;
	HWND hWnd;

private:
	void InitializeWindow(int& screenWidth, int& screenHeight);
public:
	System();
	void Initialize();
	void Run();
	void Frame();
	void Release();

	LRESULT CALLBACK MessageHandler(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
};
static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
static System* applicationHandler = NULL;