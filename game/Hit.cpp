﻿#include "Hit.h"

 

Hit::Hit(float X, float Y)
{
	this->x = X;
	this->y = Y;
	_texture = TextureManager::GetInstance()->GetTexture(eType::HIT);
	_sprite = new GSprite(_texture, 250);

}

Hit::~Hit()
{
}

void Hit::Update(DWORD dt)
{
	Effect::Update(dt);
	if (_sprite->GetCurrentFrame() == 1) // nếu là frame cuối thì xong, frame cuối trống
		isFinish = true;
}
