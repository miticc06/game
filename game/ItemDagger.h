#ifndef __ITEMDAGGER_H__
#define __ITEMDAGGER_H__
 
#include "Item.h"
#include "TextureManager.h"

#define ITEMDAGGER_TIMEDISPLAYMAX 3000
#define ITEMDAGGER_GRAVITY 0.25f


class ItemDagger : public Item
{
public:
	ItemDagger(float X = 0, float Y = 0);
	~ItemDagger();

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPOBJECT> *listObject = NULL); // Update và xét va chạm đất


};



#endif 

