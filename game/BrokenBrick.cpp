#include "BrokenBrick.h"
  
BrokenBrick::BrokenBrick(int X, int Y, int Model)
{
	this->x = X;
	this->y = Y;
	_texture = TextureManager::GetInstance()->GetTexture(eID::BROKENBRICK);
	_sprite = new GSprite(_texture, 50);
	_model = Model;
	switch (_model)
	{
	case 1:
	{
		
		break;
	}

	case 2:
	{

		break;
	}

	case 3:
	{

		break;
	}

	case 4:
	{

		break;
	}
	}
}

void BrokenBrick::Update(DWORD dt)
{
	Effect::Update(dt);
	if (_sprite->GetIndex() == _sprite->_end) // nếu là frame cuối thì xong,
		isFinish = true;

}




BrokenBrick::~BrokenBrick()
{
}
