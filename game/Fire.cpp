#include "Fire.h"

Fire::Fire(int X, int Y)
{
	this->x = X;
	this->y = Y;
	_texture = TextureManager::GetInstance()->GetTexture(eType::FIRE);
	_sprite = new GSprite(_texture, 150);
}


Fire::~Fire()
{
}

void Fire::Update(DWORD dt)
{
	Effect::Update(dt);
	if (_sprite->GetIndex() == 3) // nếu là frame cuối thì xong, frame cuối trống
		isFinish = true;
}
