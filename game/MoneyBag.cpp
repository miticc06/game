#include "MoneyBag.h"
 

MoneyBag::MoneyBag(float X, float Y, eType TypeMoneyBag)
{
	type = TypeMoneyBag;
	_texture = TextureManager::GetInstance()->GetTexture(eType::BONUS);
	_sprite = new GSprite(_texture, 0);

	this->x = X;
	this->y = Y;

	vx = 0;

	vy = MONEYBAG_GRAVITY;
	TimeDisplayMax = MONEYBAG_TIMEDISPLAYMAX; // set time hiển thị tối đa
	TimeDisplayed = 0;
	TimeWaited = 0;
	TimeWaitMax = MONEYBAG_TIMEWAITMAX;

}

void MoneyBag::Render(Camera * camera)
{
	if (isWaitingDisplay())
	{
		return;
	}

	switch (type)
	{ 
	case eType::MONEY_BAG_RED:
		_sprite->SelectIndex(MONEYBAG_ANI_RED);
		break;

	case eType::MONEY_BAG_WHITE:
		_sprite->SelectIndex(MONEYBAG_ANI_WHITE);
		break;

	case eType::MONEY_BAG_PURPLE:
		_sprite->SelectIndex(MONEYBAG_ANI_PURPLE);
		break;
	}

	D3DXVECTOR2 pos = camera->Transform(x, y);
	_sprite->Draw(pos.x, pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
}

MoneyBag::~MoneyBag()
{
}
