#ifndef __GAMETIME_H__
#define __GAMETIME_H__

#include "define.h"

class GameTime
{
private:
	DWORD _accumulationTime; // thời gian đã tích lũy
	int _time; // time game
	DWORD _frameStart;
	bool isJustChanged; // kiểm tra có phải biến time vừa được cập nhật?

public:
	GameTime();
	~GameTime();
	void Update();
	void SetTime(int t);
	int GetTime();
	bool CheckIsJustChanged();
};




#endif 

