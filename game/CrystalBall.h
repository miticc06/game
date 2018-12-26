#ifndef __CRYSTALBALL_H__
#define __CRYSTALBALL_H__
#include "Item.h"


#define CRYSTALBALL_GRAVITY 0.25f
#define CRYSTALBALL_TIMEWAITMAX 300
#define CRYSTALBALL_DEFAULT_POSITION_X 5368.0f
#define CRYSTALBALL_DEFAULT_POSITION_y 216.0f

class CrystalBall :
	public Item
{
public:
	CrystalBall(float X, float Y);
	virtual ~CrystalBall(); 

 	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *listObject = NULL);
	virtual void Render(Camera * camera);

};

#endif