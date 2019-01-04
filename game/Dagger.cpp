#include "Dagger.h"



Dagger::Dagger(Camera *camera)
{
	type = eType::DAGGER;
 	_texture = TextureManager::GetInstance()->GetTexture(type);
	_sprite = new GSprite(_texture, 0);
	this->camera = camera;
}


Dagger::~Dagger()
{
}

void Dagger::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{  
	//if (!isStart) // vũ khí chưa bắt đầu thì tiếp tục update và thoát
	//{
	//	Weapon::UpdateIsStart(dt);
	//	return;
	//}

	if (!camera->checkObjectInCamera(x, y, (float)GetWidth(), (float)GetHeight())) // xử lí ra khỏi cam thì kết thúc 
	{
		isFinish = true;
		return;
	}
	 
	GameObject::Update(dt); // update dt,dx,dy 
	x += dx;
	 
}

void Dagger::Create(float simonX, float simonY, int simonDirection)
{
	Weapon::Create(simonX, simonY + 10, simonDirection);
	vx = DAGGER_SPEED * direction;
	Sound::GetInstance()->Play(eSound::soundDagger);
}
 

void Dagger::RenderIcon(float X, float Y)
{
	_sprite->DrawFrameFlipX(0, X, Y); 
}
  