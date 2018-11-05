#include "Simon.h"



Simon::Simon()
{
	_texture = new GTexture("Resources\\simon.png", 8, 3, 24, SHOWBOX_PINK);
	_sprite = new GSprite(_texture, 100);
	type = eID::SIMON;

	isWalking = 0;
	isJumping = 0;
	isSitting = 0;

}


Simon::~Simon()
{
}

void Simon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (isSitting == true) // simon đang ngồi
	{
		left = x; 
		top = y; // không chỉnh lại y bởi vì hàm Sit() đã điều chỉnh
		right = x + SIMON_BBOX_WIDTH;
		bottom = y + SIMON_BBOX_SITTING_HEIGHT;
	}
	else
	{
		left = x;
		top = y;
		right = x + SIMON_BBOX_WIDTH;
		bottom = y + SIMON_BBOX_HEIGHT;
	}
 	
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	/* Update về sprite */

	int index = _sprite->GetIndex();

	if (isSitting == 1)
	{
		_sprite->SelectIndex(SIMON_ANI_SITTING);
	}
	else
		if (isWalking == 1) // đang di chuyển
		{
			if (index < SIMON_ANI_BEGIN_WALKING || index >= SIMON_ANI_END_WALKING)
				_sprite->SelectIndex(1);

			//cập nhật frame mới
			_sprite->Update(dt); // dt này được cập nhật khi gọi update; 
		}
		else
			_sprite->SelectIndex(SiMON_ANI_IDLE);		// SIMON đứng yên

	 
	/* Update về sprite */








	GameObject::Update(dt);  	// Calculate dx, dy 
	vy = 0;

	//vy += SIMON_GRAVITY * dt;// Simple fall down

	 

	x += dx;
	y += dy;



}

void Simon::Render()
{ 




	if (trend == -1)
		_sprite->Draw(x, y);
	else
		_sprite->DrawFlipX(x, y);
	 

}

void Simon::SetState(int state)
{
	
	GameObject::SetState(state);

	switch (state)
	{
	case SIMON_STATE_IDLE:
		vx = 0; 
		break;
	case SIMON_STATE_WALKING:
		vx = SIMON_WALKING_SPEED;
		break;


	default:
		break;
	}



}

void Simon::Left()
{
	trend = -1;
}

void Simon::Right()
{
	trend = 1; // quay qua phải
}

void Simon::Go()
{
	vx = SIMON_WALKING_SPEED * trend;
	isWalking = 1;
}

void Simon::Sit()
{
	if (isSitting == false) // nếu trước đó simon chưa ngồi
		y = y + 16; // kéo simon xuống

	isSitting = 1;
}

void Simon::Stop()
{
	vx = 0;
	isWalking = 0;
	if (isSitting == true) // nếu simon đang ngồi
	{
		isSitting = 0; // hủy trạng thái ngồi
		y = y - 16; // kéo simon lên
	}
	
}
