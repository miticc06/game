#include "PotRoast.h"

 

PotRoast::PotRoast(float X, float Y)
{
	type = eType::POTROAST;
	_texture = TextureManager::GetInstance()->GetTexture(type);
	_sprite = new GSprite(_texture, 100);

	x = X;
	y = Y;
	Health = 1;

	vy = POTROAST_GRAVITY;
	TimeDisplayMax = POTROAST_TIMEDISPLAYMAX; // set time hiển thị tối đa
	TimeDisplayed = 0;
	TimeWaited = 0;
	TimeWaitMax = POTROAST_TIMEWAITMAX;

}

PotRoast::~PotRoast()
{
}
 