#include "ThrowingAxe.h"



ThrowingAxe::ThrowingAxe(Camera * camera)
{
	type = eType::THROWINGAXE;
	_texture = TextureManager::GetInstance()->GetTexture(type);
	_sprite = new GSprite(_texture, 70);


	_spriteIcon = new GSprite(TextureManager::GetInstance()->GetTexture(eType::ITEMTHROWINGAXE), 0);
	 
	isFinish = true;
	this->camera = camera;
}


ThrowingAxe::~ThrowingAxe()
{
	if (Sound::GetInstance()->isPlaying(eSound::soundAxe))
		Sound::GetInstance()->Stop(eSound::soundAxe);
}

void ThrowingAxe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!camera->checkObjectInCamera(x,y,GetWidth(),GetHeight())) // xử lí ra khỏi cam thì kết thúc
	{ 
		isFinish = true;

		if (Sound::GetInstance()->isPlaying(eSound::soundAxe))
			Sound::GetInstance()->Stop(eSound::soundAxe);

		return;
	}

	GameObject::Update(dt); //update dt dx d 
	vy += THROWINGAXE_GRAVITY * dt;
	 
	y += dy;
	x += dx;

	_sprite->Update(dt);
}

void ThrowingAxe::Create(float simonX, float simonY, int simonDirection)
{
	if (isFinish == false)
		return;
	Weapon::Create(simonX, simonY, simonDirection);
	UpdatePositionFitSimon();
	vx = THROWINGAXE_SPEED_X * simonDirection;
	vy = -THROWINGAXE_SPEED_Y;
	 
	Sound::GetInstance()->Play(eSound::soundAxe, true);
}

void ThrowingAxe::RenderIcon(int X, int Y)
{
	_spriteIcon->Draw(X, Y);
}
