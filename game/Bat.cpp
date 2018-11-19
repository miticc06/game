#include "Bat.h"

 
Bat::Bat(float X, float Y, int Trend)
{
	_texture = TextureManager::GetInstance()->GetTexture(eID::BAT);
	_sprite = new GSprite(_texture, 70);
	type = eID::BAT;

	this->x = X;
	this->y = Y;
	this->yBackup = y;
	this->trend = Trend;
	this->Health = 1;

	vy = BAT_SPEED_Y;
	vx = BAT_SPEED_X* Trend;
}

Bat::~Bat()
{
}

void Bat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + _texture->FrameWidth;
	bottom = y + _texture->FrameHeight;

}

void Bat::Update(DWORD dt, vector<LPOBJECT>* listObject)
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

}

void Bat::Render(Camera * camera)
{
	if (Health <= 0)
		return;

	_sprite->Update(dt);
	if (_sprite->GetIndex()==0)
		_sprite->Update(dt);
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (trend == -1)
		_sprite->Draw((int)pos.x, (int)pos.y);
	else
		_sprite->DrawFlipX((int)pos.x, (int)pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
}
