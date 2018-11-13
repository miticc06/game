#ifndef __SMALLHEART_H__
#define __SMALLHEART_H__


#include "Item.h"

#define SMALLHEART_GRAVITY 0.04f
#define SMALLHEART_TIMEDISPLAYMAX 6000
#define SMALLHEART_TIMEWAITMAX 150

#define SMALLHEART_SPEED_X 0.05f

#define DeltaX 25 //px


class SmallHeart :	public Item
{
private:
	float xBackup; // vị trí của x ban dầu

public:
	SmallHeart(float X = 0, float Y = 0);

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPOBJECT> *listObject = NULL); // Update và xét va chạm đất


	virtual ~SmallHeart();
};


 
#endif 
