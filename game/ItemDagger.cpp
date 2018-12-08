#include "ItemDagger.h"


 
ItemDagger::ItemDagger(float X, float Y)
{
 	_texture = TextureManager::GetInstance()->GetTexture(eType::ITEMDAGGER);
	_sprite = new GSprite(_texture, 0);
	type = eType::ITEMDAGGER;

	this->x = X;
	this->y = Y;
	vy = ITEMDAGGER_GRAVITY;
	TimeDisplayMax = ITEMDAGGER_TIMEDISPLAYMAX;
	TimeDisplayed = 0;
	TimeWaited = 0;
	TimeWaitMax = ITEMDAGGER_TIMEWAITMAX;
}
 
 



ItemDagger::~ItemDagger()
{
}
