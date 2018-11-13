#include "SmallHeart.h"


 

SmallHeart::SmallHeart(float X, float Y)
{
	_texture = TextureManager::GetInstance()->GetTexture(eID::SMALLHEART);

	_sprite = new GSprite(_texture, 100);
	type = eID::SMALLHEART;

	this->x = X;
	this->y = Y;
	this->xBackup = X;

	TimeDisplayMax = SMALLHEART_TIMEDISPLAYMAX; // set time hiển thị tối đa
	TimeDisplayed = 0;
	TimeWaited = 0;
	TimeWaitMax = SMALLHEART_TIMEWAITMAX;


	vy = SMALLHEART_GRAVITY;
	vx = SMALLHEART_SPEED_X;
}

void SmallHeart::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + _texture->FrameWidth;
	bottom = y + _texture->FrameHeight;
}

void SmallHeart::Update(DWORD dt, vector<LPOBJECT>* listObject)
{
	if (TimeWaited < TimeWaitMax)
	{
		TimeWaited += dt;
		return;
	}

	TimeDisplayed += dt;
	if (TimeDisplayed >= TimeDisplayMax)
	{
		isFinish = true;
		return;
	}

	// vượt quá biên độ trục x cho phép thì đổi chiều vx
	if (x - xBackup >= DeltaX)
	{
		vx = -SMALLHEART_SPEED_X;
	}
	else
		if (x - xBackup <= -DeltaX)
		{
			vx = SMALLHEART_SPEED_X;
		}


	Item::Update(dt); // Update dt, dx, dy


	vector<LPOBJECT> listObject_Brick;
	listObject_Brick.clear();
	for (UINT i = 0; i < listObject->size(); i++)
		if (listObject->at(i)->GetType() == eID::BRICK)
			listObject_Brick.push_back(listObject->at(i));

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(&listObject_Brick, coEvents); // Lấy danh sách các va chạm

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		y += dy;
		x += dx;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		y += min_ty * dy + ny * 0.4f;

		if (ny != 0)
		{
			vy = 0;
			vx = 0; // cho dừng di chuyển theo biên độ x
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];

}

SmallHeart::~SmallHeart()
{
}
