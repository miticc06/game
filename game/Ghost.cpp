#include "Ghost.h"

 

Ghost::Ghost(float X,  float Y, int Trend)
{
	x = X;
	y = Y;
	this->trend = Trend;

	_texture = TextureManager::GetInstance()->GetTexture(eID::GHOST);
	_sprite = new GSprite(_texture, 100);

	Health = 1; // sét máu

	vx = GHOST_SPEED* this->trend;
}

Ghost::~Ghost()
{
}

void Ghost::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + _texture->FrameWidth;
	bottom = y + _texture->FrameHeight;
}

void Ghost::Update(DWORD dt, vector<LPOBJECT>* coObjects)
{
	GameObject::Update(dt);
	x += dx;
}
