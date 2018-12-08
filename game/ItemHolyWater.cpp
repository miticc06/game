#include "ItemHolyWater.h"


 
	 

ItemHolyWater::ItemHolyWater(float X, float Y)
{
	_texture = TextureManager::GetInstance()->GetTexture(eType::ITEMHOLYWATER);
	_sprite = new GSprite(_texture, 0);
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
 