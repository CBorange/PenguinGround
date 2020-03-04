#include"TimeManagement.h"

TimeManagement* TimeManagement::Inst = nullptr;

TimeManagement::TimeManagement()
{
	deltaTime = 0;
	oldTime = timeGetTime();
	curTime = timeGetTime();
}

TimeManagement* TimeManagement::GetInst()
{
	if (Inst == nullptr)
		Inst = new TimeManagement();
	return Inst;
}

void TimeManagement::CheckDeltaTime()
{
	curTime = timeGetTime();
	deltaTime = curTime - oldTime;
	oldTime = curTime;
}
float TimeManagement::GetDeltaTime()
{
	deltaTime = deltaTime * 0.001f;
	return deltaTime;
}