#include "ItemBoomerang.h"



ItemBoomerang::ItemBoomerang(float X, float Y)
{
	type = eType::ITEMBOOMERANG;

	_texture = TextureManager::GetInstance()->GetTexture(type);
	_sprite = new GSprite(_texture, 100);

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
