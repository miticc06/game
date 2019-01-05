#include "ItemThrowingAxe.h"



ItemThrowingAxe::ItemThrowingAxe(float X, float Y)
{
	texture = TextureManager::GetInstance()->GetTexture(eType::ITEMTHROWINGAXE);
	sprite = new GSprite(texture, 0);
	type = eType::ITEMTHROWINGAXE;

	this->x = X;
	this->y = Y;
	vy = ITEMTHROWINGAXE_GRAVITY;
	TimeDisplayMax = ITEMTHROWINGAXE_TIMEDISPLAYMAX;
	TimeDisplayed = 0;
	TimeWaited = 0;
	TimeWaitMax = ITEMTHROWINGAXE_TIMEWAITMAX;
}


ItemThrowingAxe::~ItemThrowingAxe()
{
}
