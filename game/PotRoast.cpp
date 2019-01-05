#include "PotRoast.h"

 

PotRoast::PotRoast(float X, float Y)
{
	type = eType::POTROAST;
	texture = TextureManager::GetInstance()->GetTexture(type);
	sprite = new GSprite(texture, 100);

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
 