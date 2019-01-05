#include "Cross.h"


 

Cross::Cross(float X, float Y)
{
	type = eType::CROSS;
	texture = TextureManager::GetInstance()->GetTexture(type);
	sprite = new GSprite(texture, 0);

	this->x = X;
	this->y = Y;
	vy = CROSS_GRAVITY;
	TimeDisplayMax = CROSS_TIMEDISPLAYMAX;
	TimeDisplayed = 0;
	TimeWaited = 0;
	TimeWaitMax = CROSS_TIMEWAITMAX;
}

Cross::~Cross()
{
}
