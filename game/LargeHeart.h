#ifndef __LARGEHEART_H__
#define __LARGEHEART_H__


#include "Item.h"
#include "VariableGlobal.h"

#define LARGEHEART_GRAVITY 0.25f

#define LARGEHEART_TIMEDISPLAYMAX 3000

class LargeHeart :
	public Item
{
public:
	LargeHeart();
	LargeHeart(float X, float Y);

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPOBJECT> *listObject = NULL);
	void SetReward();


	~LargeHeart();
};




#endif 

