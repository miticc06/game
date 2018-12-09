#include "ItemDagger.h"


 
ItemDagger::ItemDagger(float X, float Y)
{
	type = eType::ITEMDAGGER;
 	_texture = TextureManager::GetInstance()->GetTexture(type);
	_sprite = new GSprite(_texture, 0);

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
