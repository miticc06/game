#ifndef __FIRE_H__
#define __FIRE_H__

#include "Effect.h"

#define FIRE_WIDTH 32
#define FIRE_HEIGHT 28


class Fire : public Effect
{
private:
	int CountNeedLoop;// số lần lặp

public:
	Fire(float X=0, float Y=0, int CountLoop = 1);
	~Fire(); 

	void Update(DWORD dt);

};



#endif // !__FIRE_H__

