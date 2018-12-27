#include "Boomerang.h"

 


Boomerang::Boomerang(Camera * camera, GameObject* simon)
{
	type = eType::BOOMERANG;
 	_texture = TextureManager::GetInstance()->GetTexture(type);
	_sprite = new GSprite(_texture, 70);

	_spriteIcon = new GSprite(TextureManager::GetInstance()->GetTexture(eType::ITEMBOOMERANG), 0);

	isFinish = true;
	this->camera = camera;
	this->simon = simon;
}
 

void Boomerang::RenderIcon(int X, int Y)
{
	_spriteIcon->Draw(X, Y);

}

void Boomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{


	GameObject::Update(dt); //update dt dx dy
	x += dx;

	switch (StatusProcess)
	{
	case BOOMERANG_STATUS_PROCESS_1: // b1 boomerang đi theo hướng ném
	{
		if (abs(xCreate - x) >= BOOMERANG_LIMIT_DISTANCE_X || !camera->CHECK_OBJECT_IN_CAMERA(this)) // khoảng cách giữa vị trí bắt đầu và hiện tại vượt quá 285 thì đổi hướng
		{
			x -= dx;
			vx *= -1;
			StatusProcess = BOOMERANG_STATUS_PROCESS_2;
		}
		break;
	}

	case BOOMERANG_STATUS_PROCESS_2: // b2 boomerang đi ngược hướng ném
	{
		if (!camera->CHECK_OBJECT_IN_CAMERA(this) || isCollision(simon)) // nếu boomerang ra khỏi cam, hoặc quay lại chạm simon
		{
			isFinish = true;
			if (Sound::GetInstance()->isPlaying(eSound::soundBoomerang))
				Sound::GetInstance()->Stop(eSound::soundBoomerang); 
		} 
		break;
	}

	}
	

	_sprite->Update(dt);

}

void Boomerang::Create(float X, float Y, int Direction)
{
	if (isFinish == false)
		return;
	Weapon::Create(X, Y, Direction);
	UpdatePositionFitSimon();
	vx = BOOMERANG_SPEED_X * Direction;
	vy = 0;

	StatusProcess = BOOMERANG_STATUS_PROCESS_1; // ném theo hướng simon

	xCreate = X;

	Sound::GetInstance()->Play(eSound::soundBoomerang, true);
}

Boomerang::~Boomerang()
{
}
