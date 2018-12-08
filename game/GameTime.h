#ifndef __GAMETIME_H__
#define __GAMETIME_H__

#include "define.h"

class GameTime
{
private:
	DWORD _accumulationTime; // thời gian đã tích lũy
	int _time; // time game 
	bool isJustChanged; // kiểm tra có phải biến time vừa được cập nhật?

public:
	GameTime();
	~GameTime();
	void Update(DWORD dt);
	void SetTime(int t);
	int GetTime();
	bool CheckIsJustChanged();
};




#endif 

