#include "HolyWater.h"



HolyWater::HolyWater()
{
	_texture = TextureManager::GetInstance()->GetTexture(eType::HOLYWATER);
	_sprite = new GSprite(_texture, 70);
	type = eType::HOLYWATER;
	_spriteIcon = new GSprite(TextureManager::GetInstance()->GetTexture(eType::ITEMHOLYWATER), 200);

	isCollisionBrick = false;
	isFinish = true;
}

HolyWater::~HolyWater()
{
	
}

void HolyWater::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isFinish)
		return;

	Weapon::Update(dt); //update dt dx d
	if (!isCollisionBrick)
		vy += HOLYWATER_GRAVITY * dt;

	vector<LPGAMEOBJECT> listObject_Brick;
	listObject_Brick.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->GetType() == eType::BRICK)
			listObject_Brick.push_back(coObjects->at(i));

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult; 
	coEvents.clear(); 
	CalcPotentialCollisions(&listObject_Brick, coEvents); // Lấy danh sách các va chạm 
	if (coEvents.size() == 0)
	{
		y += dy; 
		x += dx;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny; 
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		x += min_tx * dx + nx * 0.4f;	
		y += min_ty * dy + ny * 0.4f;
		if (nx != 0)
		{
			vy = 0;
			vx = 0;
			isCollisionBrick = true;

		}

		if (ny != 0)
		{
			vy = 0;
			vx = 0;
			isCollisionBrick = true;
 		}

	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i]; 
}

void HolyWater::Create(float simonX, float simonY, int simonDirection)
{
	if (isFinish == false)
		return;
	Weapon::Create(simonX, simonY, simonDirection);
	UpdatePositionFitSimon();
	vx = HOLLYWATER_SPEED_X * simonDirection;
	vy = - HOLLYWATER_SPEED_Y;
	isCollisionBrick = false;
	_sprite->SelectIndex(0);
	Sound::GetInstance()->Play(eSound::soundHolyWater);
}

void HolyWater::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x-5;
	top = y;
	right = x + _texture->FrameWidth+5;
	bottom = y + _texture->FrameHeight;
	if (_sprite->GetIndex() == 0) // frame đầu
	{
		left += 5;
		top += 5;
		right -= 5;
		bottom -= 0;
	}
}

void HolyWater::UpdatePositionFitSimon()
{
	y += 20;
}

void HolyWater::RenderIcon(int X, int Y)
{
	_spriteIcon->Draw(X,Y);
}
 

void HolyWater::Render(Camera * camera)
{
	if (!camera->checkObjectInCamera(x, y, _texture->FrameWidth, _texture->FrameHeight))
		isFinish = true;

	if (isFinish == true)
		return;

	if (isCollisionBrick) // chạm đất r thì mới update ani
		_sprite->Update(dt);
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (direction == -1)
		_sprite->Draw((int)pos.x, (int)pos.y);
	else
		_sprite->DrawFlipX((int)pos.x, (int)pos.y);
	 
	if (IS_DEBUG_RENDER_BBOX)
	{
 		RenderBoundingBox(camera);
	}
	if (_sprite->GetIndex() == 3) // là frame cuối cùng thì kết thúc
	{
		isFinish = true;
	}
}
 