#include "FireBall.h"



FireBall::FireBall()
{
	_texture = TextureManager::GetInstance()->GetTexture(eType::FIREBALL);
	_sprite = new GSprite(_texture, 0);
	type = eType::FIREBALL;
	isFinish = true;
}


FireBall::~FireBall()
{
}

void FireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isFinish)
		return;

	Weapon::Update(dt); // update dt,dx,dy 
	x += dx; 
	y += dy;
	// xử lí ra khỏi cam thì xóa
	 
}

void FireBall::Create(float X, float Y, int Direction)
{
	if (!isFinish)
		return;
	Weapon::Create(X, Y, Direction);
	//vx = FIREBALL_SPEED * direction;
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
	if (isFinish)
		return false;
	// dt, dx, dy đã update
	GameObject *gameObj = dynamic_cast<GameObject*>(obj);
	if (gameObj->GetHealth() <= 0) // vật này die rồi thì ko va chạm
		return false;
	return isCollitionObjectWithObject(obj);
}

void FireBall::Render(Camera * camera)
{
	if (isFinish)
		return;
	if (x + _sprite->_texture->FrameWidth < camera->GetXCam() || 
		x > camera->GetXCam()+ camera->GetWidth() ||

		y + _sprite->_texture->FrameHeight < camera->GetYCam() ||
		y > camera->GetYCam() + camera->GetHeight() 

		) // ra khỏi cam thì kết thúc
	{
		isFinish = true;
		return;
	} 
	Weapon::Render(camera);
}
