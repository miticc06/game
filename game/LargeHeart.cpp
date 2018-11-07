#include "LargeHeart.h"



LargeHeart::LargeHeart()
{
	_texture = new GTexture("Resources\\item\\1.png");
	_sprite = new GSprite(_texture, 100);
	
}

LargeHeart::LargeHeart(float X, float Y) : LargeHeart()
{
	this->x = X;
	this->y = Y;
	vy = LARGEHEART_GRAVITY;
	TimeDisplayMax = LARGEHEART_TIMEDISPLAYMAX; // set time hiển thị tối đa
}

void LargeHeart::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + _texture->FrameWidth;
	bottom = y + _texture->FrameHeight;
}

void LargeHeart::Update(DWORD dt, GameObject * listObject)
{



}



LargeHeart::~LargeHeart()
{
}
