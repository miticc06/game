#ifndef  __ITEMBOOMERANG_H__
#define __ITEMBOOMERANG_H__

#define ITEMBOOMERANG_GRAVITY 0.25f
#define ITEMBOOMERANG_TIMEDISPLAYMAX 3000
#define ITEMBOOMERANG_TIMEWAITMAX 300

#include "Item.h"
class ItemBoomerang :
	public Item
{
public:
	ItemBoomerang(float X, float Y);
	virtual ~ItemBoomerang();
};

#endif