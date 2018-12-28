#include "MorningStar.h"



MorningStar::MorningStar()
{
	type = eType::MORNINGSTAR;
	_texture = TextureManager::GetInstance()->GetTexture(type);
	_sprite = new GSprite(_texture, MORNINGSTAR_TIME_WAIT_ANI);
	this->level = 0;
}


MorningStar::~MorningStar()
{
}

void MorningStar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{ 
	GameObject::Update(dt);

	// update for check collision

	isFinish = (_sprite->GetIndex() == 3 && level == 0) + (_sprite->GetIndex() == 7 && level == 1) + (_sprite->GetIndex() == 11 && level == 2);

	int StartFrame = MORNINGSTAR_ANI_LEVEL0_START + 4 * level; // ánh xạ chỉ số frame bằng level thay vì ifelse 
	int EndFrame = MORNINGSTAR_ANI_LEVEL0_END + 4 * level;


	if (StartFrame <= _sprite->GetIndex() && _sprite->GetIndex() < EndFrame)
		_sprite->Update(dt);
	else
	{
		_sprite->SelectIndex(StartFrame);
	}
		

	//DebugOut(L"update ani Morningstar dt = %d, tich luy = %d\n", dt, _sprite->_timeLocal);

}

void MorningStar::Render(Camera * camera)
{
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (direction == -1)
		_sprite->Draw(pos.x, pos.y);
	else
		_sprite->DrawFlipX(pos.x, pos.y);


	if (IS_DEBUG_RENDER_BBOX)
	{
		if (level == 0 && _sprite->GetIndex() == MORNINGSTAR_ANI_LEVEL0_START || _sprite->GetIndex() == MORNINGSTAR_ANI_LEVEL0_START + 1)
			return; // frame đầu và frame chuẩn bị đánh thì vẽ BBOX

		if (level == 1 && _sprite->GetIndex() == MORNINGSTAR_ANI_LEVEL1_START || _sprite->GetIndex() == MORNINGSTAR_ANI_LEVEL1_START + 1)
			return;

		if (level == 2 && _sprite->GetIndex() == MORNINGSTAR_ANI_LEVEL2_START || _sprite->GetIndex() == MORNINGSTAR_ANI_LEVEL2_START + 1)
			return; 
		RenderBoundingBox(camera);
	}
		
}
 



void MorningStar::Create(float simonX, float simonY, int simonDirection)
{
 

	Weapon::Create(simonX, simonY, simonDirection);

	UpdatePositionFitSimon();
	switch (level)
	{
	case 0:
		_sprite->SelectIndex(MORNINGSTAR_ANI_LEVEL0_START); 
		_sprite->ResetTime();
		break;
	case 1:
		_sprite->SelectIndex(MORNINGSTAR_ANI_LEVEL1_START); 
		_sprite->ResetTime();

		break;
	case 2:
		_sprite->SelectIndex(MORNINGSTAR_ANI_LEVEL2_START);
		_sprite->ResetTime();

		break; 
	}
 	Sound::GetInstance()->Play(eSound::soundWhip); 
}

void MorningStar::UpdatePositionFitSimon()
{ 
	if (direction == -1)
	{
		this->x = x - 75;
		this->y -= 2;

	}
	else
	{
		this->x = x - 25;
		this->y-=2;
	}
}

void MorningStar::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	switch (level)
	{
	case 0: 
	{
		if (direction == 1)
		{
			left = x + 78;
			top = y + 15;
			right = x + _texture->FrameWidth - 30;
			bottom = y + _texture->FrameHeight - 30;
		}
		else
		{
			left = x + 30;
			top = y + 15;
			right = x + _texture->FrameWidth - 80;
			bottom = y + _texture->FrameHeight - 30;

		}
		break;
	}
	case 1:
	{
		if (direction == 1)
		{
			left = x + 78;
			top = y + 15;
			right = x + _texture->FrameWidth - 30;
			bottom = y + _texture->FrameHeight - 30;
		}
		else
		{
			left = x + 30;
			top = y + 15;
			right = x + _texture->FrameWidth - 80;
			bottom = y + _texture->FrameHeight - 30;

		}
		break;
	}
	case 2:
	{
		if (direction == 1)
		{
			left = x + 78;
			top = y + 15;
			right = x + _texture->FrameWidth;
			bottom = y + _texture->FrameHeight - 30;
		}
		else
		{
			left = x;
			top = y + 15;
			right = x + _texture->FrameWidth - 80;
			bottom = y + _texture->FrameHeight - 30;

		}
		break;
	}
	default:
		break;
	} 
 
}

void MorningStar::RenderIcon(float X, float Y)
{
}
 
void MorningStar::UpgradeLevel()
{
	if (level >= 2)
		return;

	level++;
	if (isFinish == false) // nếu chưa đánh xong mà update thì phải update lại frame để sau khi Freezed xong sẽ chạy tiếp
	{
		_sprite->SelectIndex(_sprite->GetIndex() + 4);

	}


}

int MorningStar::GetLevel()
{
	return level;
}

bool MorningStar::isCollision(GameObject * obj)
{
	if (level==0 && _sprite->GetIndex() == MORNINGSTAR_ANI_LEVEL0_START || _sprite->GetIndex() == MORNINGSTAR_ANI_LEVEL0_START + 1)
		return false; // frame đầu và frame chuẩn bị đánh thì ko xét va chạm

	if (level == 1 && _sprite->GetIndex() == MORNINGSTAR_ANI_LEVEL1_START || _sprite->GetIndex() == MORNINGSTAR_ANI_LEVEL1_START + 1)
		return false; // frame đầu và frame chuẩn bị đánh thì ko xét va chạm

	if (level == 2 && _sprite->GetIndex() == MORNINGSTAR_ANI_LEVEL2_START || _sprite->GetIndex() == MORNINGSTAR_ANI_LEVEL2_START + 1)
		return false; // frame đầu và frame chuẩn bị đánh thì ko xét va chạm
	 
	return Weapon::isCollision(obj);
}
