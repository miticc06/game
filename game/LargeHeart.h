#ifndef __LARGEHEART_H__
#define __LARGEHEART_H__


#include "Item.h" 
#include "TextureManager.h"

#define LARGEHEART_GRAVITY 0.25f
#define LARGEHEART_TIMEDISPLAYMAX 3000
#define LARGEHEART_TIMEWAITMAX 300

class LargeHeart :
	public Item
{
public:
	LargeHeart(float X =0, float Y=0);
	 

	~LargeHeart();
};




#endif 

