#include "Ghost.h"

 

Ghost::Ghost(float X,  float Y, int Trend)
{
	x = X;
	y = Y;
	this->trend = Trend;

	_texture = TextureManager::GetInstance()->GetTexture(eID::GHOST);
	_sprite = new GSprite(_texture, 100);

	Health = 1; // sét máu
	type = eID::GHOST;
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

void Ghost::Render(Camera * camera)
{
	if (Health <= 0)
		return;

	_sprite->Update(dt);

	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (trend == -1)
		_sprite->Draw((int)pos.x, (int)pos.y);
	else
		_sprite->DrawFlipX((int)pos.x, (int)pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);

}
