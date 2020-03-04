#pragma once
#include<d3d9.h>
#include<d3dx9.h>

class TimeManagement
{
private:
	float deltaTime;
	float oldTime;
	float curTime;

	static TimeManagement* Inst;
	TimeManagement();
public:
	static TimeManagement* GetInst();

	void CheckDeltaTime();
	float GetDeltaTime();
};