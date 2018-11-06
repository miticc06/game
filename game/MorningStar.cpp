#include "MorningStar.h"



MorningStar::MorningStar()
{
	_texture = new GTexture("Resources\\weapon\\morningstar.png", 4, 3, 12, 0);
	_sprite = new GSprite(_texture, 90);
	this->level = 0;
}


MorningStar::~MorningStar()
{
}

void MorningStar::Update(int dt)
{
	//if (isFinish == false)
	//{
	//	if (level == 0 && _sprite->GetIndex() == MORNINGSTAR_ANI_LEVEL0_END) // nếu nó chạy frame cuối rồi
	//	{
	//		isFinish = true;
	//		return;
	//	} 
	//}

	isFinish = (_sprite->GetIndex() == 3) + (_sprite->GetIndex() == 7) + (_sprite->GetIndex() == 11);


	if (level == 0)
	{
		if (MORNINGSTAR_ANI_LEVEL0_START <= _sprite->GetIndex() && _sprite->GetIndex() < MORNINGSTAR_ANI_LEVEL0_END)
		{
			_sprite->Update(dt);
		}
		else
		{
			_sprite->SelectIndex(MORNINGSTAR_ANI_LEVEL0_START);
		} 
	}
}

void MorningStar::Create(float simonX, float simonY, int simonTrend)
{
 

	Weapon::Create(simonX, simonY, simonTrend);

	UpdatePositionFitSimon();

	if (level == 0)
	{
		_sprite->SelectIndex(MORNINGSTAR_ANI_LEVEL0_START - 1); // đặt sai index cho hàm update cập nhật ngay frame đầu
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
