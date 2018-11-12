#include "GameTime.h"



GameTime::GameTime()
{
	this->_accumulationTime = 0;
	_frameStart = GetTickCount();

}


GameTime::~GameTime()
{
}

void GameTime::Update()
{
	DWORD now = GetTickCount();
	DWORD dt = now - _frameStart;

	DebugOut(L"dt time = %d \n", dt);

	if (_accumulationTime + dt < 1000)
	{
		_accumulationTime += dt;
	}
	else
	{
		_accumulationTime = (_accumulationTime + dt) % 1000;
		_time++;
		isJustChanged = true; // set trạng thái vừa thay đổi
	}

	_frameStart = now;


}

void GameTime::SetTime(int t)
{
	_time = t;
}

int GameTime::GetTime()
{
	return _time;
}

bool GameTime::CheckIsJustChanged()
{
	bool b = isJustChanged;
	isJustChanged = false; // sau khi lấy trạng thái xong rồi thì coi như "chưa thay đổi"
	return b;
}
