#include "Item.h"



Item::Item()
{ 
	TimeDisplayed = 0;
	TimeWaitMax = 0;
	TimeDisplayMax = 0;
	TimeWaited = 0;
	isFinish = 0;
}


Item::~Item()
{
	 
}

void Item::Update(DWORD dt, vector<LPGAMEOBJECT> *listObject)
{ 
	

	if (isWaitingDisplay())
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

	GameObject::Update(dt, listObject);

	vector<LPGAMEOBJECT> listObject_Brick;
	listObject_Brick.clear();
	for (UINT i = 0; i < listObject->size(); i++)
		if (listObject->at(i)->GetType() == eType::BRICK)
			listObject_Brick.push_back(listObject->at(i));

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	CalcPotentialCollisions(&listObject_Brick, coEvents); // Lấy danh sách các va chạm 
	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		y += min_ty * dy + ny * 0.4f;
		if (ny != 0)
		{
			vy = 0;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}

void Item::Render(Camera * camera)
{
	if (isWaitingDisplay())
	{ 
		return;
	}

	D3DXVECTOR2 pos = camera->Transform(x, y);

	_sprite->Draw(pos.x, pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
}

bool Item::isWaitingDisplay()
{
	return TimeWaited < TimeWaitMax;
}
 



bool Item::GetFinish()
{
	return isFinish;
}

void Item::SetFinish(bool b)
{
	isFinish = b;
}
