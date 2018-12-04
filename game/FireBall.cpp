#include "FireBall.h"



FireBall::FireBall()
{
	_texture = TextureManager::GetInstance()->GetTexture(eType::FIREBALL);
	_sprite = new GSprite(_texture, 0);
	type = eType::FIREBALL;
}


FireBall::~FireBall()
{
}

void FireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Weapon::Update(dt); // update dt,dx,dy 
	x += dx; 
	// xử lí ra khỏi cam thì xóa
}

void FireBall::Create(float X, float Y, int Direction)
{
	Weapon::Create(X, Y, Direction);
	vx = FIREBALL_SPEED * direction;
}

void FireBall::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + _texture->FrameWidth;
	bottom = y + _texture->FrameHeight;
}

void FireBall::RenderIcon(int X, int Y)
{
}

bool FireBall::isCollision(GameObject * obj)
{
	// dt, dx, dy đã update
	GameObject *gameObj = dynamic_cast<GameObject*>(obj);
	if (gameObj->GetHealth() <= 0) // vật này die rồi thì ko va chạm
		return false;
	return isCollitionObjectWithObject(obj);
}

void FireBall::Render(Camera * camera)
{
	if (x - camera->GetXCam() + _sprite->_texture->FrameWidth < 0 || 
		x - camera->GetXCam() > camera->GetWidth()) // ra khỏi cam thì kết thúc
	{
		isFinish = true;
		return;
	} 
	Weapon::Render(camera);
}
