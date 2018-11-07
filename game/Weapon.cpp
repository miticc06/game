#include "Weapon.h"



Weapon::Weapon()
{
	isFinish = 1;
}


Weapon::~Weapon()
{ 
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

void Weapon::Update(DWORD dt, vector<LPOBJECT>* coObjects)
{
	_sprite->Update(dt);
}
 

void Weapon::Render(Camera * camera)
{
	//DebugOut(L"WEAPON: index = %d \n", _sprite->GetIndex());
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (trend == -1)
		_sprite->Draw(pos.x, pos.y);
	else
		_sprite->DrawFlipX(pos.x, pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
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
 

Item * Weapon::GetNewItem(int Id, eID Type, float X, float Y)
{
	if (Type == eID::TORCH)
	{
		if (Id == 1 || Id == 4)
			return new LargeHeart(X, Y);

		if (Id == 2 || Id == 3)
			return new UpgradeMorningStar(X, Y);

		return new LargeHeart(X, Y);

	}
}