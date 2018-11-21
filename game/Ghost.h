#ifndef __GHOST_H__
#define __GHOST_H__


#define GHOST_SPEED_X 0.08f
#define GHOST_GRAVITY 0.005f


#include "Enemy.h"
class Ghost : public GameObject
{
public:
	Ghost(float X, float Y, int Trend);
	virtual ~Ghost();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera *camera);



};


#endif  


