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


#ifndef BROKEN_BRICK_ADD_EFFECT
#define BROKEN_BRICK_ADD_EFFECT(listEffect, gameObject) \
listEffect.push_back(new BrokenBrick(gameObject->GetX() + 14, gameObject->GetY() + 14, 1));\
listEffect.push_back(new BrokenBrick(gameObject->GetX() + 14,gameObject->GetY() + 14, 2));\
listEffect.push_back(new BrokenBrick(gameObject->GetX() + 14, gameObject->GetY() + 14, 3));\
listEffect.push_back(new BrokenBrick(gameObject->GetX() + 14, gameObject->GetY() + 14, 4));\

#endif