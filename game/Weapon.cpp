#include "Weapon.h"



Weapon::Weapon()
{
	isFinish = 1;
}


Weapon::~Weapon()
{ 
}

int Weapon::GetDirection()
{
	return direction;
}

void Weapon::SetDirection(int Direction)
{
	this->direction = Direction;
}

void Weapon::Create(float X, float Y, int Direction)
{
	this->x = X;
	this->y = Y;
	this->direction = Direction;
	isFinish = 0;
	
	LastTimeAttack = GetTickCount(); // lưu lại thời điểm lúc vừa tấn công, làm đánh dấu tránh 1 hit đánh nhiều lần cho các object, có health >1.
}

void Weapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;
	
}
 

void Weapon::Render(Camera * camera)
{
	//DebugOut(L"WEAPON: index = %d \n", _sprite->GetIndex());
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (direction == -1)
		_sprite->Draw((int)pos.x, (int)pos.y);
	else
		_sprite->DrawFlipX((int)pos.x, (int)pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
}
 

void Weapon::UpdatePositionFitSimon()
{
}

bool Weapon::isCollision(GameObject * obj)
{
	if (isFinish == true)
		return false;
	// dt, dx, dy đã update 
	if (obj->GetHealth() <= 0) // vật này die rồi thì ko va chạm
		return false;
	return isCollitionObjectWithObject(obj);
}
 
 

bool Weapon::GetFinish()
{
	return isFinish;
}

void Weapon::SetFinish(bool b)
{
	isFinish = b;
}

DWORD Weapon::GetLastTimeAttack()
{
	return LastTimeAttack;
}
 
