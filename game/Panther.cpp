#include "Panther.h"



Panther::Panther(float X, float Y, int Trend)
{
	type = eID::PANTHER;
	Health = 1;
	vx = vy = 0;
	trend = Trend;
	x = X;
	y = Y;

	_texture = TextureManager::GetInstance()->GetTexture(eID::PANTHER);
	_sprite = new GSprite(_texture, 200);

	isSitting = true;
	isRunning = false;

	

}



void Panther::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + _texture->FrameWidth;
	bottom = y + _texture->FrameHeight;
}

void Panther::Update(DWORD dt, Simon * simon, vector<LPOBJECT>* coObjects)
{
	GameObject::Update(dt);


	if (abs(simon->GetX() - (x+_texture->FrameWidth)) <= 177.0f)
	{
		isSitting = false;
		isRunning = true;
		// chuyển qua trạng thái chạy
	}

	
	if (isSitting)
	{
		_sprite->SelectIndex(PANTHER_ANI_SITTING);
	}
	else
	{
		if (isRunning)
		{
			if (PANTHER_ANI_RUNNING_BEGIN <= _sprite->GetIndex() && _sprite->GetIndex() < PANTHER_ANI_RUNNING_END)
			{
				_sprite->Update(dt);
			}
			else
				_sprite->SelectIndex(PANTHER_ANI_RUNNING_BEGIN);
		}
	}
}

void Panther::Render(Camera * camera)
{
	if (Health <= 0)
		return;

//	_sprite->Update(dt);

	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (trend == -1)
		_sprite->Draw((int)pos.x, (int)pos.y);
	else
		_sprite->DrawFlipX((int)pos.x, (int)pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);

}



Panther::~Panther()
{
}
