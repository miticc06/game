#include "Fishmen.h"

 
Fishmen::Fishmen(float X, float Y, int Direction)
{
	_texture = TextureManager::GetInstance()->GetTexture(eType::FISHMEN);
	_sprite = new GSprite(_texture, 70);
	type = eType::FISHMEN;

	this->x = X;
	this->y = Y; 
	this->direction = Direction;
	this->Health = 1; 
	vx = 0;
	vy = -FISHMEN_SPEED_Y_UP;
	yInit = y;
	isAllowRunAnimation = false;
	_sprite->SelectIndex(FISHMEN_ANI_JUMP);
}

Fishmen::~Fishmen()
{
}

void Fishmen::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + _texture->FrameWidth;
	bottom = y + _texture->FrameHeight;
}

void Fishmen::Update(DWORD dt, vector<LPGAMEOBJECT>* listObject)
{
	if (y <= yInit - FISHMEN_DY_JUMP)
	{ 
		vy = FISHMEN_SPEED_Y_DOWN;
	}
	 

	GameObject::Update(dt); // update dt,dx,dy 
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult; 
	coEvents.clear(); 
	vector<LPGAMEOBJECT> list_Brick;
	list_Brick.clear();
	for (UINT i = 0; i < listObject->size(); i++)
		if (listObject->at(i)->GetType() == eType::BRICK)
			list_Brick.push_back(listObject->at(i)); 
	CalcPotentialCollisions(&list_Brick, coEvents);
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		x += min_tx * dx + nx * 0.4f;
		if (nx != 0)
			vx = 0;

		if (ny == -1)
		{
			vy = 0;
			y += min_ty * dy + ny * 0.4f;
			isAllowRunAnimation = true;
		}
		else
			y += dy;
	} 
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i]; 
}

void Fishmen::Render(Camera * camera)
{
	if (Health <= 0)
		return;

	if (isAllowRunAnimation)
		;//	_sprite->Update(dt);
	 
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (direction == -1)
		_sprite->Draw((int)pos.x, (int)pos.y);
	else
		_sprite->DrawFlipX((int)pos.x, (int)pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
}
