#include"System.h"
#include"D3D.h"
#include"InputManagement.h"
#include"TimeManagement.h"

System::System()
{
	D3DClass = nullptr;
	hInst = nullptr;
	hWnd = nullptr;
}

void System::Initialize()
{
	D3DClass = D3D::GetInst();

	int screenWidth, screenHeight;
	screenWidth = 1920;
	screenHeight = 1080;

	InitializeWindow(screenWidth, screenHeight);
}
void System::InitializeWindow(int& screenWidth, int& screenHeight)
{
	hInst = GetModuleHandle(NULL);
	applicationName = L"PenguinGround";

	WNDCLASSEX wc = { 0, };
	wc.cbSize = sizeof(wc);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInst;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = applicationName;
	wc.lpszMenuName = NULL;
	wc.style = CS_OWNDC;

	RegisterClassEx(&wc);

	if (FULL_SCREEN)
	{  
		hWnd = CreateWindowEx(WS_EX_APPWINDOW, applicationName, applicationName,
			WS_EX_TOPMOST | WS_POPUP, CW_USEDEFAULT, CW_USEDEFAULT, screenWidth,
			screenHeight, NULL, NULL, hInst, NULL);
	}
	else
	{
		hWnd = CreateWindowEx(WS_EX_APPWINDOW, applicationName, applicationName,
			WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, screenWidth,
			screenHeight, NULL, NULL, hInst, NULL);
	}

	D3DClass->Create(hWnd, screenWidth, screenHeight);
	D3DClass->Initialize();

	ShowWindow(hWnd, SW_SHOW);
	SetFocus(hWnd);
}
void System::Run()
{
	MSG msg;
	memset(&msg, 0, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Frame();
		}
	}
}
void System::Frame()
{
	InputManagement::GetInst()->CheckKeyState();
	D3DClass->Frame();
}
void System::Release()
{
	UnregisterClass(applicationName, hInst);

	D3DClass->Release();
	DestroyWindow(hWnd);
}
LRESULT CALLBACK System::MessageHandler(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_MOUSEMOVE:
		break;
	case WM_KEYDOWN:
		InputManagement::GetInst()->ChangeAnyKeyToDown();
		break;
	case WM_KEYUP:
		InputManagement::GetInst()->ChangeAnyKeyToUp();
		break;
	}
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_CREATE:
		srand(unsigned int(timeGetTime()));
		AllocConsole();
		SetConsoleTitle(L"Debug");
		_tfreopen(L"CONOUT$", L"w", stdout);
		_tfreopen(L"CONIN$", L"r", stdin);
		_tfreopen(L"CONERR$", L"w", stderr);
		_tsetlocale(LC_ALL, L"");
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CLOSE:
		FreeConsole();
		PostQuitMessage(0);
		DestroyWindow(hWnd);
		return 0;
	case WM_QUIT:
		FreeConsole();
		PostQuitMessage(0);
		DestroyWindow(hWnd);
		return 0;
	default:
		applicationHandler->MessageHandler(hWnd, iMsg, wParam, lParam);
	}
}