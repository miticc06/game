#ifndef __UPGRADEMORNINGSTAR_H__
#define __UPGRADEMORNINGSTAR_H__


#define UPGRADEMORNINGSTAR_GRAVITY 0.25f

#define UPGRADEMORNINGSTAR_TIMEDISPLAYMAX 3000

#include "Item.h"
class UpgradeMorningStar :
	public Item
{


public:
	UpgradeMorningStar();
	UpgradeMorningStar(float X, float Y);

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPOBJECT> *listObject = NULL);
	void SetReward();


	~UpgradeMorningStar();
};

#endif  



