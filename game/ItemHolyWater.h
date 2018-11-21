#ifndef __ITEMHOLYWATER_H__
#define __ITEMHOLYWATER_H__

#define ITEMHOLYWATER_TIMEDISPLAYMAX 3000
#define ITEMHOLYWATER_GRAVITY 0.25f
#define ITEMHOLYWATER_TIMEWAITMAX 300
#include "Item.h"
class ItemHolyWater : public Item
{
public:
	ItemHolyWater(float X = 0, float Y = 0);
	virtual ~ItemHolyWater();

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *listObject = NULL); // Update và xét va chạm đất

};

 
#endif