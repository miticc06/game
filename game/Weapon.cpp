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
}

void Weapon::SetPosition(float X, float Y)
{
	this->x = X;
	this->y = Y;
}

void Weapon::UpdatePositionFitSimon()
{
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
