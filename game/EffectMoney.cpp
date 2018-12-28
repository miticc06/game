#include "EffectMoney.h"
 


EffectMoney::EffectMoney(float X, float Y, eType typeEffectMoney)
{
	_texture = TextureManager::GetInstance()->GetTexture(typeEffectMoney);
	_sprite = new GSprite(_texture, 2000);

	this->x = X + 40;
	this->y = Y - 20;
}

void EffectMoney::Update(DWORD dt)
{
	Effect::Update(dt);
	if (_sprite->GetCurrentFrame() == 1) // nếu là frame cuối thì xong, frame cuối trống
		isFinish = true;
}

EffectMoney::~EffectMoney()
{
}
