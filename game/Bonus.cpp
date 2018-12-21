#include "Bonus.h"


 

Bonus::Bonus(float X, float Y)
{
	type = eType::BONUS;
	_texture = TextureManager::GetInstance()->GetTexture(type);
	_sprite = new GSprite(_texture, 20);

	this->x = X;
	this->y = Y;
	
	  
	vx = 0;
	vy = 0;

	vy = MONEY_GRAVITY; // tam thoi




	TimeDisplayMax = MONEY_TIMEDISPLAYMAX; // set time hiển thị tối đa
	TimeDisplayed = 0;
	TimeWaited = 0;
	TimeWaitMax = MONEY_TIMEWAITMAX;
		 
}

Bonus::~Bonus()
{
}

void Bonus::Render(Camera * camera)
{

	Item::Render(camera);
	_sprite->Update(dt);
}
 