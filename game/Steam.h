#ifndef __STEAM_H__
#define __STEAM_H__
  
#define STEAM_GRAVITY 0.0015f 

#include "Effect.h"

class Steam : public Effect
{
private: 
	int _model;
	DWORD dt;
	float dx;
	float dy;
	float vx;
	float vy;

public:
	Steam(float X, float Y, int Model);
	virtual ~Steam();

	void Update(DWORD dt);
 
};

#endif