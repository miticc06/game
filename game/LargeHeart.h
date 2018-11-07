#pragma once
#include "Item.h"

#define LARGEHEART_GRAVITY 0.005f

#define LARGEHEART_TIMEDISPLAYMAX 200

class LargeHeart :
	public Item
{
public:
	LargeHeart();
	LargeHeart(float X, float Y);
	
	


	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, GameObject * listObject);
	void Render(Camera * camera);






	~LargeHeart();
};

