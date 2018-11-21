#ifndef __BROKENBRICK_H__
#define __BROKENBRICK_H__
 
#include "Effect.h"

#define BROKENBRICK_GRAVITY 0.005f 


class BrokenBrick : public Effect
{
private:
	int _model;

public:
	BrokenBrick(int X, int Y, int Model);
	virtual ~BrokenBrick();
	void Update(DWORD dt);
};


#endif 