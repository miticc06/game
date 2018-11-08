#include "MorningStar.h"



MorningStar::MorningStar()
{
	_texture = new GTexture("Resources\\weapon\\morningstar.png", 4, 3, 12, 0);
	_sprite = new GSprite(_texture, 90);
	this->level = 0;
	type = eID::MORNINGSTAR;
}


MorningStar::~MorningStar()
{
}

void MorningStar::Update(DWORD dt, vector<LPOBJECT>* coObjects)
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

	if (level == 1)
	{
		if (MORNINGSTAR_ANI_LEVEL1_START <= _sprite->GetIndex() && _sprite->GetIndex() < MORNINGSTAR_ANI_LEVEL1_END)
		{
			_sprite->Update(dt);
		}
		else
		{
			_sprite->SelectIndex(MORNINGSTAR_ANI_LEVEL1_START);
		}
	}
}
 

void MorningStar::Create(float simonX, float simonY, int simonTrend)
{
 

	Weapon::Create(simonX, simonY, simonTrend);

	//xBackup, yBackup

	UpdatePositionFitSimon();

	if (level == 0)
	{
		_sprite->SelectIndex(MORNINGSTAR_ANI_LEVEL0_START - 1); // đặt sai index cho hàm update cập nhật ngay frame đầu
	}

	if (level == 1)
	{
		_sprite->SelectIndex(MORNINGSTAR_ANI_LEVEL1_START - 1); // đặt sai index cho hàm update cập nhật ngay frame đầu
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
	if (level == 0)
	{
		if (trend == 1)
		{
			left = x + 80;  
			top = y + 15;
			right = x + _texture->FrameWidth -30; 
			bottom = y + _texture->FrameHeight - 30;
		}
		else
		{
			left = x + 30;
			top = y + 15;
			right = x + _texture->FrameWidth - 85;
			bottom = y + _texture->FrameHeight - 30;

		}

	}

	if (level == 1)
	{
		if (trend == 1)
		{
			left = x + 80;
			top = y + 15;
			right = x + _texture->FrameWidth - 30;
			bottom = y + _texture->FrameHeight - 30;
		}
		else
		{
			left = x + 30;
			top = y + 15;
			right = x + _texture->FrameWidth - 85;
			bottom = y + _texture->FrameHeight - 30;

		}

	}

}

void MorningStar::CollisionWithObject(DWORD dt, vector<LPOBJECT>* listObj)
{
	if (_sprite->GetIndex() == MORNINGSTAR_ANI_LEVEL0_START || _sprite->GetIndex() == MORNINGSTAR_ANI_LEVEL0_START + 1)
		return;

	RECT rect, rect1;
	float l, t, r, b;
	float l1, t1, r1, b1;

	GetBoundingBox(l, t, r, b);
	rect.left = (int)l;
	rect.top = (int)t;
	rect.right = (int)r;
	rect.bottom = (int)b;



	for (int i = 0; i < listObj->size(); i++) // ngay đây có thể tối ưu thêm, từ từ fix :p
		if (listObj->at(i)->GetType() == eID::TORCH)
		{
			GameObject *obj = dynamic_cast<GameObject*>(listObj->at(i));
			if (obj->GetHealth() > 0)
			{
				listObj->at(i)->GetBoundingBox(l1, t1, r1, b1);
				rect1.left = (int)l1;
				rect1.top = (int)t1;
				rect1.right = (int)r1;
				rect1.bottom = (int)b1;
				if (Game::GetInstance()->AABBCheck(rect, rect1))
				{
					obj->SubHealth(1);
					VariableGlobal::GetInstance()->ListItem.push_back(Weapon::GetNewItem(obj->id, obj->GetType(), listObj->at(i)->GetX(), listObj->at(i)->GetY()));
				}
			}
		}
	 

}

void MorningStar::UpgradeLevel()
{
	if (level >= 2)
		return;
	level++;
}
