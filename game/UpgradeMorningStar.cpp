#include "UpgradeMorningStar.h"

 

UpgradeMorningStar::UpgradeMorningStar(float X, float Y) 
{
	texture = TextureManager::GetInstance()->GetTexture(eType::UPGRADEMORNINGSTAR);
	sprite = new GSprite(texture, 100);
	type = eType::UPGRADEMORNINGSTAR;

	this->x = X;
	this->y = Y;
	vy = UPGRADEMORNINGSTAR_GRAVITY;
	
	TimeDisplayed = 0;
	TimeDisplayMax = UPGRADEMORNINGSTAR_TIMEDISPLAYMAX; // set time hiển thị tối đa
	TimeWaited = 0;
	TimeWaitMax = UPGRADEMORNINGSTAR_TIMEWAITMAX;


}
 
 

UpgradeMorningStar::~UpgradeMorningStar()
{
}
