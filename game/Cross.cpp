#include "Cross.h"


 

Cross::Cross(float X, float Y)
{
	type = eType::CROSS;
	_texture = TextureManager::GetInstance()->GetTexture(type);
	_sprite = new GSprite(_texture, 0);

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
