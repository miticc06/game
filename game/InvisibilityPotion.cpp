#include "InvisibilityPotion.h"
 

InvisibilityPotion::InvisibilityPotion(float X, float Y)
{
	type = eType::INVISIBILITYPOTION; 
	_texture = TextureManager::GetInstance()->GetTexture(type);
	_sprite = new GSprite(_texture, 0);

	this->x = X;
	this->y = Y;

	vy = INVISIBILITYPOTION_GRAVITY;
	TimeDisplayMax = INVISIBILITYPOTION_TIMEDISPLAYMAX;
	TimeDisplayed = 0;
	TimeWaited = 0;
	TimeWaitMax = INVISIBILITYPOTION_TIMEWAITMAX;
}

InvisibilityPotion::~InvisibilityPotion()
{
}
