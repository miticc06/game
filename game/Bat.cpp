#include "Bat.h"

 
Bat::Bat(float X, float Y, int Direction)
{
	type = eType::BAT;
	_texture = TextureManager::GetInstance()->GetTexture(type);
	_sprite = new GSprite(_texture, 70);
	 
	this->x = X;
	this->y = Y;
	this->yBackup = y;
	this->direction = Direction;
	this->Health = 1;

	vy = BAT_SPEED_Y;
	vx = BAT_SPEED_X* Direction;
}

Bat::~Bat()
{
}
 

void Bat::Update(DWORD dt, vector<LPGAMEOBJECT>* listObject)
{  
	// vượt quá biên độ trục y cho phép thì đổi chiều vy
	if (y - yBackup >= DeltaY)
	{
		vy = -BAT_SPEED_Y;
	}
	else
		if (y - yBackup <= -DeltaY)
		{
			vy = BAT_SPEED_Y;
		}


	GameObject::Update(dt); // Update dt, dx, dy

	y += dy;
	x += dx;

	_sprite->Update(dt);
	if (_sprite->GetIndex() == 0)
		_sprite->Update(dt);
}

void Bat::Render(Camera * camera)
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
