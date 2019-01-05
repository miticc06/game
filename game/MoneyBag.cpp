#include "MoneyBag.h"
 

MoneyBag::MoneyBag(float X, float Y, eType TypeMoneyBag)
{
	type = TypeMoneyBag;
	texture = TextureManager::GetInstance()->GetTexture(eType::BONUS);
	sprite = new GSprite(texture, 0);

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
		sprite->SelectFrame(MONEYBAG_ANI_RED);
		break;

	case eType::MONEY_BAG_WHITE:
		sprite->SelectFrame(MONEYBAG_ANI_WHITE);
		break;

	case eType::MONEY_BAG_PURPLE:
		sprite->SelectFrame(MONEYBAG_ANI_PURPLE);
		break;
	}

	D3DXVECTOR2 pos = camera->Transform(x, y);
	sprite->Draw(pos.x, pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
}

MoneyBag::~MoneyBag()
{
}
