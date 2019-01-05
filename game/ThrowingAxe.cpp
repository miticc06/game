#include "ThrowingAxe.h"



ThrowingAxe::ThrowingAxe(Camera * camera)
{
	type = eType::THROWINGAXE;
	texture = TextureManager::GetInstance()->GetTexture(type);
	sprite = new GSprite(texture, 70);


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
	if (!camera->checkObjectInCamera(x,y, (float)GetWidth(), (float)GetHeight())) // xử lí ra khỏi cam thì kết thúc
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

	sprite->Update(dt);
}

void ThrowingAxe::Attack(float X, float Y, int Direction)
{
	if (isFinish == false)
		return;
	Weapon::Attack(X, Y, Direction);
	UpdatePositionFitSimon();
	vx = THROWINGAXE_SPEED_X * Direction;
	vy = -THROWINGAXE_SPEED_Y;
	 
	Sound::GetInstance()->Play(eSound::soundAxe, true);
}

void ThrowingAxe::RenderIcon(float X, float Y)
{
	_spriteIcon->Draw(X, Y);
}
