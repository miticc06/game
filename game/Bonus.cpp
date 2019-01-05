#include "Bonus.h"


 

Bonus::Bonus(float X, float Y)
{
	type = eType::BONUS;
	texture = TextureManager::GetInstance()->GetTexture(type);
	sprite = new GSprite(texture, 20);

	this->x = X;
	this->y = Y;
	
	  
	vx = 0;
	vy = 0;

	vy = BONUS_GRAVITY; 
	 
	TimeDisplayMax = BONUS_TIMEDISPLAYMAX; // set time hiển thị tối đa
	TimeDisplayed = 0;
	TimeWaited = 0;
	TimeWaitMax = BONUS_TIMEWAITMAX;
		 
}

Bonus::~Bonus()
{
}

void Bonus::Render(Camera * camera)
{

	Item::Render(camera);
	sprite->Update(dt);
}
 