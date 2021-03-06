#include<d3d9.h>
#include<d3dx9.h>
#include"System.h"

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT)
{
	System* system = new System();

	system->Initialize();

	system->Run();

	system->Release();
	delete system;
	system = NULL;

	return 0;
}