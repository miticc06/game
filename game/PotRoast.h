#ifndef __POTROAST_H__
#define __POTROAST_H__

#define POTROAST_GRAVITY 0.25f
#define POTROAST_TIMEDISPLAYMAX 3000
#define POTROAST_TIMEWAITMAX 300

#include "Item.h"
class PotRoast : public Item
{
public:
	PotRoast(int X, int Y);
	virtual ~PotRoast();
	 


}; 
#endif
