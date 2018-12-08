#include "PotRoast.h"

 

PotRoast::PotRoast(int X, int Y)
{
	_texture = TextureManager::GetInstance()->GetTexture(eType::POTROAST);
	_sprite = new GSprite(_texture, 100);

	x = X;
	y = Y;
	Health = 1;
	type = eType::POTROAST;

	vy = POTROAST_GRAVITY;
	TimeDisplayMax = POTROAST_TIMEDISPLAYMAX; // set time hiển thị tối đa
	TimeDisplayed = 0;
	TimeWaited = 0;
	TimeWaitMax = POTROAST_TIMEWAITMAX;

}

PotRoast::~PotRoast()
{
}
 