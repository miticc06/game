#include "HolyWater.h"



HolyWater::HolyWater(Camera * camera)
{
	texture = TextureManager::GetInstance()->GetTexture(eType::HOLYWATER);
	sprite = new GSprite(texture, 100);
	type = eType::HOLYWATER;
	_spriteIcon = new GSprite(TextureManager::GetInstance()->GetTexture(eType::ITEMHOLYWATER), 200);

	isCollisionBrick = false;
	isFinish = true;
	this->camera = camera;
}

HolyWater::~HolyWater()
{
	
}

void HolyWater::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!camera->checkObjectInCamera(x, y, (float)texture->GetFrameWidth(), (float)texture->GetFrameHeight()))
		isFinish = true;

	if (isFinish)
		return;

	GameObject::Update(dt); //update dt dx d
	if (!isCollisionBrick)
		vy += HOLYWATER_GRAVITY * dt;

	if (!isCollisionBrick) // chưa chạm đất mới xét va chạm
	{
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
			if (nx != 0 || ny != 0)
			{
				vy = 0;
				vx = 0;
				isCollisionBrick = true;
				Sound::GetInstance()->Play(eSound::soundHolyWater); // chạm đất thì mới playsound
			}
		}
		for (UINT i = 0; i < coEvents.size(); i++)
			delete coEvents[i];
	}
	 
}
 
void HolyWater::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x-5;
	top = y;
	right = x + texture->GetFrameWidth()+5;
	bottom = y + texture->GetFrameHeight();
	if (sprite->GetCurrentFrame() == 0) // frame đầu
	{
		left += 5;
		top += 5;
		right -= 5;
		bottom -= 0;
	}
}

void HolyWater::UpdatePositionFitSimon()
{
	y += 15;
	if (this->direction == -1)
		x += 30;
		
}

void HolyWater::Attack(float X, float Y, int Direction)
{
	if (isFinish == false)
		return;
	Weapon::Attack(X, Y, Direction);
	UpdatePositionFitSimon();
	vx = HOLLYWATER_SPEED_X * Direction;
	vy = -HOLLYWATER_SPEED_Y;
	isCollisionBrick = false;
	sprite->SelectFrame(0);
	CountLoop = 0;
}

void HolyWater::RenderIcon(float X, float Y)
{
	_spriteIcon->Draw(X,Y);
}
 

void HolyWater::Render(Camera * camera)
{ 
	if (isFinish == true)
		return;

	if (isCollisionBrick) // chạm đất r thì mới update ani
		sprite->Update(dt);

	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (direction == -1)
		sprite->Draw(pos.x, pos.y);
	else
		sprite->DrawFlipX(pos.x, pos.y);

	if (IS_DEBUG_RENDER_BBOX)
	{
 		RenderBoundingBox(camera);
	}

	if (sprite->GetCurrentFrame() == 3) // là frame cuối cùng thì kết thúc
	{ 
		CountLoop++;
		if (CountLoop >= 2) // lặp đúng 2 lần thì dừng
			isFinish = true;
		else
			sprite->SelectFrame(1);
	}
}
 