#ifndef __BONUS_H__
#define __BONUS_H__



#include "Item.h"


#define BONUS_TIMEDISPLAYMAX 5000
#define BONUS_TIMEWAITMAX 300
#define BONUS_GRAVITY 0.25f




class Bonus : public Item
{
public:
	Bonus(float X = 0, float Y = 0);
	~Bonus();
	void Render(Camera * camera);
};




#endif

