#include "Steam.h"


 

Steam::Steam(float X, float Y, int Model)
{ 
	 this->x = X;
	 this->y = Y;
	 dx = dy = vx = vy = 0;
	 _texture = TextureManager::GetInstance()->GetTexture(eType::STEAM);
	 _sprite = new GSprite(_texture, 50);
	 _model = Model; 
	 switch (_model)
	 {
	 case STEAM_MODEL_1:
	 { 
 		 vy = -0.4f;
		 vx = -0.04f;
		 break;
	 }

	 case STEAM_MODEL_2:
	 {
 		 vy = -0.5f;
		 vx = 0.0f;
		 break;
	 } 
	 case STEAM_MODEL_3:
	 {
		 vy = -0.4f;
		 vx = 0.1f;
		 break;
	 } 
	 }
}

Steam::~Steam()
{
}

void Steam::Update(DWORD dt)
{
	this->dt = dt;
	this->dx = vx * dt;
	this->dy = vy * dt;

	vy += STEAM_GRAVITY * dt;

	x += dx;
	y += dy;
}
