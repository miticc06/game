#ifndef __GHOST_H__
#define __GHOST_H__


#define GHOST_SPEED_X 0.09f
#define GHOST_GRAVITY 0.005f


#include "GameObject.h"
class Ghost : public GameObject
{
public:
	Ghost(float X, float Y, int Direction);
	virtual ~Ghost();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera *camera);



};


#endif  


