#ifndef __GHOST_H__
#define __GHOST_H__


#define GHOST_SPEED 0.05f

#include "Enemy.h"
class Ghost : public Enemy
{
public:
	Ghost(float X, float Y, int Trend);
	virtual ~Ghost();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPOBJECT> *coObjects = NULL);



};


#endif  


