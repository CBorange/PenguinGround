#include"InputManagement.h"
InputManagement* InputManagement::Inst = nullptr;

InputManagement::InputManagement()
{
	keyState = nullptr;
	keyState = new InputState[151];
	anyKey = new InputState();
}

InputManagement* InputManagement::GetInst()
{
	if (Inst == nullptr)
		Inst = new InputManagement();
	return Inst;
}

void InputManagement::ChangeAnyKeyToDown()
{
	if (anyKey->pressed)
		anyKey->down = false;
	else
		anyKey->down = true;

	anyKey->up = false;
	anyKey->released = false;

	anyKey->pressed = true;
}
void InputManagement::ChangeAnyKeyToUp()
{
	if (anyKey->released)
		anyKey->up = false;
	else
		anyKey->up = true;

	anyKey->down = false;
	anyKey->pressed = false;

	anyKey->released = true;
}
void InputManagement::CheckKeyState()
{
	for (int i = 0; i < 151; ++i)
	{
		if (GetAsyncKeyState(i) & 0x8000)
		{
			if (keyState[i].pressed)
				keyState[i].down = false;
			else
				keyState[i].down = true;

			keyState[i].up = false;
			keyState[i].released = false;

			keyState[i].pressed = true;
		}
		if (!(GetAsyncKeyState(i) & 0x8000))
		{
			if (keyState[i].released)
				keyState[i].up = false;
			else
				keyState[i].up = true;

			keyState[i].down = false;
			keyState[i].pressed = false;

			keyState[i].released = true;
		}
	}
}
//Get InputState
bool InputManagement::GetKeyDown(int keyCode)
{
	if (keyState[keyCode].down)
		return true;
	return false;
}
bool InputManagement::GetKeyUp(int keyCode)
{
	if (keyState[keyCode].up)
		return true;
	return false;
}
bool InputManagement::GetKey(int keyCode)
{
	if (keyState[keyCode].pressed)
		return true;
	return false;
}
bool InputManagement::AnyKeyDown()
{
	if (anyKey->down)
		return true;
	return false;
}
bool InputManagement::AnyKeyUp()
{
	if (anyKey->up)
		return true;
	return false;
}