#include "LargeHeart.h"


 
LargeHeart::LargeHeart(float X, float Y)
{
 	_texture = TextureManager::GetInstance()->GetTexture(eType::LARGEHEART);

	_sprite = new GSprite(_texture, 100);
	type = eType::LARGEHEART;

	this->x = X;
	this->y = Y;
	vy = LARGEHEART_GRAVITY;
	TimeDisplayMax = LARGEHEART_TIMEDISPLAYMAX; // set time hiển thị tối đa
	TimeDisplayed = 0;
	TimeWaited = 0;
	TimeWaitMax = LARGEHEART_TIMEWAITMAX;
}
 

LargeHeart::~LargeHeart()
{
}
