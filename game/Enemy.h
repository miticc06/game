#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "GameObject.h"
class Enemy : public GameObject
{
public:
	Enemy();
	virtual ~Enemy();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera);

}; 


#endif  


