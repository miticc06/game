#include "Weapon.h"



Weapon::Weapon()
{
	isFinish = 1;
}


Weapon::~Weapon()
{
	SAFE_DELETE(_texture);
	SAFE_DELETE(_sprite);
}

int Weapon::GetTrend()
{
	return trend;
}

void Weapon::SetTrend(int Trend)
{
	this->trend = Trend;
}

void Weapon::Create(float simonX, float simonY, int simonTrend)
{
	this->x = simonX;
	this->y = simonY;
	this->trend = simonTrend;
	isFinish = 0;
}

void Weapon::Update(int dt)
{
	_sprite->Update(dt);
}

void Weapon::Draw(Camera * camera)
{
	DebugOut(L"WEAPON: index = %d \n", _sprite->GetIndex());
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (trend == -1)
		_sprite->Draw(pos.x, pos.y);
	else
		_sprite->DrawFlipX(pos.x, pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
}

void Weapon::SetPosition(float X, float Y)
{
	this->x = X;
	this->y = Y;
}

void Weapon::UpdatePositionFitSimon()
{
}

void Weapon::RenderBoundingBox(Camera * camera)
{

	RECT rect;

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	D3DXVECTOR2 pos = camera->Transform(l, t);

	LPDIRECT3DTEXTURE9  _Texture = DebugRenderBBOX::GetInstance()->GetTexture();

	Game::GetInstance()->Draw(pos.x, pos.y, _Texture, rect.left, rect.top, rect.right, rect.bottom, 100);

}

int Weapon::GetFinish()
{
	return isFinish;
}

void Weapon::SetFinish(bool b)
{
	isFinish = b;
}

eID Weapon::GetType()
{
	return TypeWeapon;
}
