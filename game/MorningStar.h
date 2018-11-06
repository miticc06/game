#ifndef __MORNINGSTAR_H__
#define __MORNINGSTAR_H__


#define MORNINGSTAR_ANI_LEVEL0_START 0
#define MORNINGSTAR_ANI_LEVEL0_END 3


#include "Weapon.h"
#include "GameObject.h"

class MorningStar : public Weapon
{
protected:
	int level;

public:
	MorningStar();
	~MorningStar();
	void Update( int dt);
	void Create(float simonX, float simonY, int simonTrend); 

	void UpdatePositionFitSimon();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	void CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>* listObj);

};



#endif // !__MORNINGSTAR_H__
