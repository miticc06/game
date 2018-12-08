#ifndef __ITEMSTOPWATCH_H__
#define __ITEMSTOPWATCH_H__

#define STOPWATCH_GRAVITY 0.25f
#define STOPWATCH_TIMEDISPLAYMAX 3000
#define STOPWATCH_TIMEWAITMAX 300


#include "Item.h"
class ItemStopWatch :
	public Item
{
public:
	ItemStopWatch(float X, float Y);
	~ItemStopWatch();
	 

};

#endif