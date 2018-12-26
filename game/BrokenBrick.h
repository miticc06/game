#ifndef __BROKENBRICK_H__
#define __BROKENBRICK_H__
 
#include "Effect.h"

#define BROKENBRICK_GRAVITY 0.0015f 


class BrokenBrick : public Effect
{
private:
	int _model;
	DWORD dt;
	float dx;
	float dy;
	float vx;
	float vy;
	int direction;


public:
	BrokenBrick(float X, float Y, int Model);
	virtual ~BrokenBrick();
	void Update(DWORD dt);
};


#endif 