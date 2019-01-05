#include "ItemHolyWater.h"


 
	 

ItemHolyWater::ItemHolyWater(float X, float Y)
{
	texture = TextureManager::GetInstance()->GetTexture(eType::ITEMHOLYWATER);
	sprite = new GSprite(texture, 0);
	type = eType::ITEMHOLYWATER;

	this->x = X;
	this->y = Y;
	vy = ITEMHOLYWATER_GRAVITY;
	TimeDisplayMax = ITEMHOLYWATER_TIMEDISPLAYMAX;
	TimeDisplayed = 0;
	TimeWaited = 0;
	TimeWaitMax = ITEMHOLYWATER_TIMEWAITMAX;
}

ItemHolyWater::~ItemHolyWater()
{
}
 