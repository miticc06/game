#ifndef __HELICOPTER_H__
#define __HELICOPTER_H__

#include "GameObject.h"

#define HELICOPTER_SPEED_X 0.02f
#define HELICOPTER_SPEED_Y 0.008f


class HeliCopter :
	public GameObject
{
public:
	HeliCopter(float X = 0, float Y = 0);
	virtual ~HeliCopter();
	 
	void Update(DWORD dt, vector<LPGAMEOBJECT> *listObject = NULL);
	void Render(Camera * camera);
};
#endif
