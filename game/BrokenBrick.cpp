#include "BrokenBrick.h"
  
BrokenBrick::BrokenBrick(float X, float Y, int Model)
{
	this->x = X;
	this->y = Y;
	dx = dy = vx = vy = 0;
	_texture = TextureManager::GetInstance()->GetTexture(eType::BROKENBRICK);
	_sprite = new GSprite(_texture, 3000);
	_model = Model;

	switch (_model)
	{
	case 1: // trai
	{
		direction = -1;
		vx = direction * 0.15f;
		vy = -0.25f;
		break;
	}

	case 2:// phải
	{
		direction = 1;
		vx = direction * 0.15f;
		vy = -0.2f;
		break;
	}

	case 3:// trai
	{

		direction = -1;
		vx = direction * 0.07f;
		vy = -0.22f;
		break;	}

	case 4:// phải
	{

		direction = 1;
		vx = direction * 0.1f;
		vy = -0.3f;
		break;
	} 
	}
}

void BrokenBrick::Update(DWORD dt)
{
	this->dt = dt;
	this->dx = vx * dt;
	this->dy = vy * dt;

	vy += BROKENBRICK_GRAVITY *dt;

	x += dx;
	y += dy;

	Effect::Update(dt);
	if (_sprite->GetIndex() == _sprite->_end) // nếu là frame cuối thì xong,
		isFinish = true;
}




BrokenBrick::~BrokenBrick()
{
}
