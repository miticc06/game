#include "Dagger.h"



Dagger::Dagger(Camera *camera)
{
 	_texture = TextureManager::GetInstance()->GetTexture(eType::DAGGER);
	_sprite = new GSprite(_texture, 0);
	type = eType::DAGGER;
	this->camera = camera;
}


Dagger::~Dagger()
{
}

void Dagger::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{  
	if (!camera->checkObjectInCamera(x, y, GetWidth(), GetHeight())) // xử lí ra khỏi cam thì kết thúc 
	{
		isFinish = true;
		return;
	}

	Weapon::Update(dt); // update dt,dx,dy 
	x += dx;

	
}

void Dagger::Create(float simonX, float simonY, int simonDirection)
{
	Weapon::Create(simonX, simonY + 10, simonDirection);
	vx = DAGGER_SPEED * direction;
	Sound::GetInstance()->Play(eSound::soundDagger);
}
 

void Dagger::RenderIcon(int X, int Y)
{
	_sprite->DrawFlipXIndex(0, X, Y); 

}
 

void Dagger::Render(Camera * camera)
{
	if (isFinish)
		return; 
	Weapon::Render(camera);
}
