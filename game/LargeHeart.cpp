#include "LargeHeart.h"


 
LargeHeart::LargeHeart(float X, float Y)
{
	type = eType::LARGEHEART;

 	texture = TextureManager::GetInstance()->GetTexture(type);

	sprite = new GSprite(texture, 100);

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
