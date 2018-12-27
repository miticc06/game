#ifndef __ITEMDOUBLESHOT_H__
#define __ITEMDOUBLESHOT_H__

#define ITEMDOUBLESHOT_GRAVITY 0.25f
#define ITEMDOUBLESHOT_TIMEDISPLAYMAX 5000
#define ITEMDOUBLESHOT_TIMEWAITMAX 300

#include "Item.h"
class ItemDoubleShot :
	public Item
{
public:
	ItemDoubleShot(float X, float Y);
	virtual ~ItemDoubleShot();
};

#endif