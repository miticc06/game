#ifndef __MORNINGSTAR_H__
#define __MORNINGSTAR_H__


#define MORNINGSTAR_ANI_LEVEL0_START 0
#define MORNINGSTAR_ANI_LEVEL0_END 3

#define MORNINGSTAR_ANI_LEVEL1_START 4
#define MORNINGSTAR_ANI_LEVEL1_END 7

#include "Weapon.h"
#include "GameObject.h"
#include "VariableGlobal.h"
#include "LargeHeart.h"


class MorningStar : public Weapon
{
protected:
	int level;
	float xBackup, yBackup;
public:
	MorningStar();
	~MorningStar();
	
	void Update(DWORD dt, vector<LPOBJECT> *coObjects = NULL);
	
	void Create(float simonX, float simonY, int simonTrend);

	void UpdatePositionFitSimon();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	void CollisionWithObject(DWORD dt, vector<LPOBJECT>* listObj);

	void UpgradeLevel();

};



#endif  
