#pragma once
#include<d3d9.h>
#include<d3dx9.h>

struct InputState
{
	bool down;
	bool up;
	bool pressed;
	bool released;
	InputState()
	{
		down = up = pressed = released = false;
	}
};

class InputManagement
{
private:
	InputState* anyKey;
	InputState* keyState;
	InputManagement();
	static InputManagement* Inst;
public:
	static InputManagement* GetInst();

	void ChangeAnyKeyToDown();
	void ChangeAnyKeyToUp();
	void CheckKeyState();
	//Get InputState
	bool GetKeyDown(int keyCode);
	bool GetKeyUp(int keyCode);
	bool GetKey(int keyCode);
	bool AnyKeyDown();
	bool AnyKeyUp();
};