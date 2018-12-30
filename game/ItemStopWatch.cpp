#include "ItemStopWatch.h"


 

ItemStopWatch::ItemStopWatch(float X, float Y)
{
	type = eType::STOPWATCH;
	_texture = TextureManager::GetInstance()->GetTexture(type);

	_sprite = new GSprite(_texture, 100);

	this->x = X;
	this->y = Y;
	vy = STOPWATCH_GRAVITY;
	TimeDisplayMax = STOPWATCH_TIMEDISPLAYMAX; // set time hiển thị tối đa
	TimeDisplayed = 0;
	TimeWaited = 0;
	TimeWaitMax = STOPWATCH_TIMEWAITMAX;
}

ItemStopWatch::~ItemStopWatch()
{
}
 