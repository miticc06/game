#ifndef __FIRE_H__
#define __FIRE_H__

#include "Effect.h"

class Fire : public Effect
{


public:
	Fire(int X=0, int Y=0);
	~Fire(); 

	void Update(DWORD dt);

};



#endif // !__FIRE_H__

