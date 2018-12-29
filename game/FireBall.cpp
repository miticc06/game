#include "FireBall.h"



FireBall::FireBall(Camera *camera)
{
	_texture = TextureManager::GetInstance()->GetTexture(eType::FIREBALL);
	_sprite = new GSprite(_texture, 0);
	type = eType::FIREBALL;
	isFinish = true;
	this->camera = camera;
}


FireBall::~FireBall()
{
}

void FireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isFinish)
		return;
 
	if (!camera->CHECK_OBJECT_IN_CAMERA(this)) // ra khỏi cam thì kết thúc
	{
		isFinish = true;
		return;
	}

	GameObject::Update(dt); // update dt,dx,dy 
	x += dx; 
	y += dy;
	// xử lí ra khỏi cam thì xóa
	 
}

void FireBall::Create(float X, float Y, int Direction)
{ 
	Weapon::Create(X, Y, Direction);
	//vx = FIREBALL_SPEED * direction;
}
 
void FireBall::RenderIcon(float X, float Y)
{
}
 

void FireBall::Render(Camera * camera)
{
	if (isFinish)
		return;
	
	Weapon::Render(camera);
}
