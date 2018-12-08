#ifndef __CRYSTALBALL_H__
#define __CRYSTALBALL_H__
#include "Item.h"


#define CRYSTALBALL_GRAVITY 0.25f
#define CRYSTALBALL_TIMEWAITMAX 300
 
class CrystalBall :
	public Item
{
public:
	CrystalBall(int X, int Y);
	virtual ~CrystalBall(); 

 	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *listObject = NULL);
	virtual void Render(Camera * camera);

};

#endif