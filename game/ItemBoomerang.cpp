#include "ItemBoomerang.h"



ItemBoomerang::ItemBoomerang(float X, float Y)
{
	type = eType::ITEMBOOMERANG;

	texture = TextureManager::GetInstance()->GetTexture(type);
	sprite = new GSprite(texture, 100);

	x = X;
	y = Y;
	Health = 1;

	vy = ITEMBOOMERANG_GRAVITY;
	TimeDisplayMax = ITEMBOOMERANG_TIMEDISPLAYMAX; // set time hiển thị tối đa
	TimeDisplayed = 0;
	TimeWaited = 0;
	TimeWaitMax = ITEMBOOMERANG_TIMEWAITMAX;


}


ItemBoomerang::~ItemBoomerang()
{
}
