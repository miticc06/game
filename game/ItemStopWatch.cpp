#include "ItemStopWatch.h"


 

ItemStopWatch::ItemStopWatch(float X, float Y)
{
	_texture = TextureManager::GetInstance()->GetTexture(eType::STOPWATCH);

	_sprite = new GSprite(_texture, 100);
	type = eType::STOPWATCH;

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
 