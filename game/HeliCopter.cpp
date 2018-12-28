#include "HeliCopter.h"
 
HeliCopter::HeliCopter(float X, float Y)
{
	type = eType::HELICOPTER;
	_texture = TextureManager::GetInstance()->GetTexture(type);
	_sprite = new GSprite(_texture, 70);
 
	this->x = X;
	this->y = Y;
 	this->direction = -1;
	this->Health = 1;

	vy = - HELICOPTER_SPEED_Y;
	vx = HELICOPTER_SPEED_X * direction;
}

HeliCopter::~HeliCopter()
{
}

void HeliCopter::Update(DWORD dt, vector<LPGAMEOBJECT>* listObject)
{
	GameObject::Update(dt); // Update dt, dx, dy

	y += dy;
	x += dx;

}

void HeliCopter::Render(Camera * camera)
{
	if (Health <= 0)
		return;

	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (direction == -1)
		_sprite->Draw(pos.x, pos.y);
	else
		_sprite->DrawFlipX(pos.x, pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
}
 
