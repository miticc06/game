#include "Fire.h"

Fire::Fire(float X, float Y, int CountLoop)
{
	this->x = X;
	this->y = Y;
	_texture = TextureManager::GetInstance()->GetTexture(eType::FIRE);
	_sprite = new GSprite(_texture, 150);
	this->CountNeedLoop = CountLoop;
}


Fire::~Fire()
{
}

void Fire::Update(DWORD dt)
{
	Effect::Update(dt);

	//DebugOut(L"GetCurrentFrame = %d\n", sprite->GetCurrentFrame());
 

	if (_sprite->GetCurrentFrame() == 3) // nếu là frame cuối thì xong, frame cuối trống
	{
		CountNeedLoop--; // giảm số lần cần lặp
		if (CountNeedLoop == 0) // hết lần cần lặp thì kết thúc
			isFinish = true;
		else
		{
			_sprite->timeAccumulated = _sprite->timeAnimation; 
			//DebugOut(L"CountNeedLoop = %d\n", CountNeedLoop);
		}
	}
		
}
