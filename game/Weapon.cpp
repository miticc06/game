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
		_sprite->Draw((int)pos.x, (int)pos.y);
	else
		_sprite->DrawFlipX((int)pos.x, (int)pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
}
 

void Weapon::UpdatePositionFitSimon()
{
}
 
 

bool Weapon::GetFinish()
{
	return isFinish;
}

void Weapon::SetFinish(bool b)
{
	isFinish = b;
}
 
