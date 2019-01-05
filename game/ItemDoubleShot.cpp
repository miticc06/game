#include "ItemDoubleShot.h"



ItemDoubleShot::ItemDoubleShot(float X, float Y)
{
	type = eType::ITEMDOUBLESHOT;

	texture = TextureManager::GetInstance()->GetTexture(type);
	sprite = new GSprite(texture, 100);

	x = X;
	y = Y;
	Health = 1;

	vy = ITEMDOUBLESHOT_GRAVITY;
	TimeDisplayMax = ITEMDOUBLESHOT_TIMEDISPLAYMAX; // set time hiển thị tối đa
	TimeDisplayed = 0;
	TimeWaited = 0;
	TimeWaitMax = ITEMDOUBLESHOT_TIMEWAITMAX;
}


ItemDoubleShot::~ItemDoubleShot()
{
}
