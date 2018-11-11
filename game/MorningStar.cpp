#include "MorningStar.h"



MorningStar::MorningStar()
{
	_texture = TextureManager::GetInstance()->GetTexture(eID::MORNINGSTAR);
	_sprite = new GSprite(_texture, 90);
	this->level = 0;
	type = eID::MORNINGSTAR;
}


MorningStar::~MorningStar()
{
}

void MorningStar::Update(DWORD dt, vector<LPOBJECT>* coObjects)
{ 
	this->dt = dt;
	this->dx = vx * dt;
	this->dy = vy * dt;
	// update for check collision

	isFinish = (_sprite->GetIndex() == 3 && level == 0) + (_sprite->GetIndex() == 7 && level == 1) + (_sprite->GetIndex() == 11 && level == 2);

	int StartFrame = MORNINGSTAR_ANI_LEVEL0_START + 4 * level; // ánh xạ chỉ số frame bằng level thay vì ifelse 
	int EndFrame = MORNINGSTAR_ANI_LEVEL0_END + 4 * level;


	if (StartFrame <= _sprite->GetIndex() && _sprite->GetIndex() < EndFrame)
		_sprite->Update(dt);
	else
		_sprite->SelectIndex(StartFrame);
}
 

void MorningStar::Create(float simonX, float simonY, int simonTrend)
{
 

	Weapon::Create(simonX, simonY, simonTrend);

	UpdatePositionFitSimon();
	switch (level)
	{
	case 0:
		_sprite->SelectIndex(MORNINGSTAR_ANI_LEVEL0_START - 1); // đặt sai index cho hàm update cập nhật ngay frame đầu
		break;
	case 1:
		_sprite->SelectIndex(MORNINGSTAR_ANI_LEVEL1_START - 1); // đặt sai index cho hàm update cập nhật ngay frame đầu
		break;
	case 2:
		_sprite->SelectIndex(MORNINGSTAR_ANI_LEVEL2_START - 1); // đặt sai index cho hàm update cập nhật ngay frame đầu
		break; 
	} 
}

void MorningStar::UpdatePositionFitSimon()
{
	if (trend == -1)
	{
		this->x = x - 65;
	}
	else
	{
		this->x = x - 30;
	}
}

void MorningStar::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	switch (level)
	{
	case 0: 
	{
		if (trend == 1)
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
		if (trend == 1)
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
		if (trend == 1)
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

void MorningStar::RenderIcon(int X, int Y)
{
}
 
void MorningStar::UpgradeLevel()
{
	if (level >= 2)
		return;
	level++;
}

bool MorningStar::isCollision(Object * obj)
{
	if (level==0 && _sprite->GetIndex() == MORNINGSTAR_ANI_LEVEL0_START || _sprite->GetIndex() == MORNINGSTAR_ANI_LEVEL0_START + 1)
		return false; // frame đầu và frame chuẩn bị đánh thì ko xét va chạm

	if (level == 1 && _sprite->GetIndex() == MORNINGSTAR_ANI_LEVEL1_START || _sprite->GetIndex() == MORNINGSTAR_ANI_LEVEL1_START + 1)
		return false; // frame đầu và frame chuẩn bị đánh thì ko xét va chạm

	if (level == 2 && _sprite->GetIndex() == MORNINGSTAR_ANI_LEVEL2_START || _sprite->GetIndex() == MORNINGSTAR_ANI_LEVEL2_START + 1)
		return false; // frame đầu và frame chuẩn bị đánh thì ko xét va chạm


	GameObject *gameObj = dynamic_cast<GameObject*>(obj);
	if (gameObj->GetHealth() <= 0) // vật này die rồi thì ko va chạm
		return false;

	return isCollitionObjectWithObject(gameObj);
}
