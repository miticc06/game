#include "Simon.h"
 

Simon::Simon()
{
	_texture = new GTexture("Resources\\simon.png", 8, 3, 24, SHOWBOX_PINK);
	_sprite = new GSprite(_texture, 250);
	type = eID::SIMON;

	isWalking = 0;
	isJumping = 0;
	isSitting = 0;
	isAttacking = 0;

	Health = 16; // simon dính 16 phát là chết
	Lives = 5; // có 5 mạng sống
	HeartCollect = 5;
	score = 0;


	_weaponMain =  new MorningStar();
	_weaponSub = NULL;
}


Simon::~Simon()
{
}

void Simon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (isSitting == true) // simon đang ngồi
	{
		left = x + 15;
		top = y - 1; // không chỉnh lại y bởi vì hàm Sit() đã điều chỉnh
		right = x + SIMON_BBOX_WIDTH - 17+5;
		bottom = y + SIMON_BBOX_SITTING_HEIGHT -3;
	}
	else
	{ 
		left = x +15;
		top = y -1 ;
		right = x + SIMON_BBOX_WIDTH - 17+5;
		bottom = y + SIMON_BBOX_HEIGHT - 3;
	}
 	
}

void Simon::Update(DWORD dt, vector<LPOBJECT>* coObjects)
{ 
	/*if (isJumping)
		DebugOut(L"X = %f - Y = %f\n", x, y);
*/

	/* Không cho lọt khỏi camera */
	/*if (x < -10)
		x = -10;*/
	if (x < 0)
		x = 0.0f;
	if (x + SIMON_BBOX_WIDTH > MapWidth)
		x = (float)(MapWidth - SIMON_BBOX_WIDTH);
	/* Không cho lọt khỏi camera */


	/* Update về sprite */

	int index = _sprite->GetIndex();











	if (isAttacking == true)  
	{
		if (_weaponMain->GetFinish() == false) // nếu MorningStar đang đánh
		{ 
			_weaponMain->Update(dt);
			if (_weaponMain->GetFinish() == true)
				isAttacking = false;
		}
		else
		{
			if (_weaponSub != NULL)
			{
				isAttacking = !(SIMON_ANI_SITTING_ATTACKING_END  == index || SIMON_ANI_STANDING_ATTACKING_END  == index);
			}
		}
	}

	if (_weaponSub != NULL && _weaponSub->GetFinish() == false)
	{
		_weaponSub->Update(dt);
	}





	if (isSitting == true)
	{
		if (isAttacking == true) // tấn công
		{
			if (index < SIMON_ANI_SITTING_ATTACKING_BEGIN || index >= SIMON_ANI_SITTING_ATTACKING_END)
			{
				_sprite->SelectIndex(SIMON_ANI_SITTING_ATTACKING_BEGIN);
			}
			else
			{
				//cập nhật frame mới
				_sprite->Update(dt); // dt này được cập nhật khi gọi update; 
			} 
		}
		else
			_sprite->SelectIndex(SIMON_ANI_SITTING);
	}
	else
		if (isAttacking == true)
		{
			if (index < SIMON_ANI_STANDING_ATTACKING_BEGIN || index >= SIMON_ANI_STANDING_ATTACKING_END )
			{
				_sprite->SelectIndex(SIMON_ANI_STANDING_ATTACKING_BEGIN);
			}
			else
			{
				//cập nhật frame mới
				_sprite->Update(dt); // dt này được cập nhật khi gọi update; 
			}
		}
		else
		if (isWalking == true) // đang di chuyển
		{
			if (isJumping == false) // ko nhảy
			{
				if (index < SIMON_ANI_WALKING_BEGIN || index >= SIMON_ANI_WALKING_END)
					_sprite->SelectIndex(SIMON_ANI_WALKING_BEGIN);

				//cập nhật frame mới
				_sprite->Update(dt); // dt này được cập nhật khi gọi update; 
			}
			else
			{
				_sprite->SelectIndex(SIMON_ANI_JUMPING);
			}
			
		}
		else
			if (isJumping == true) // nếu ko đi mà chỉ nhảy
			{
				_sprite->SelectIndex(SIMON_ANI_JUMPING);
			}
			else
			{
				_sprite->SelectIndex(SiMON_ANI_IDLE);		// SIMON đứng yên

			}
	 
	/* Update về sprite */


	


	



	GameObject::Update(dt);  
	//if (isJumping)
	//{
	//	dy = vy * 2.0f;
	//	vy += /*0.0019f*/ 0.002f * 16;
	//}
	//else  
		
	
	
	vy += SIMON_GRAVITY * dt;// Simple fall down
	if (isJumping && isWalking)
	{
		dx = vx * dt *1.5f;

	}
		



	//if (isJumping == true && isWalking == true)
	//	vx += 0.0012f * dt *trend;



	vector<LPOBJECT> list_Brick;
	list_Brick.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->GetType() == eID::BRICK)
			list_Brick.push_back(coObjects->at(i));
	CollisionWithBrick(&list_Brick); // check Collision and update x, y for simon


	 





	_weaponMain->SetPosition(this->x, this->y);
	_weaponMain->UpdatePositionFitSimon();

	//_weaponMain->Update(dt);

	/*
	
	
	if (isAttacking == true) //  update postion roi sau vì kiểm tra va chạm bên trên có thể khiến x,y của simon thay đổi, gây lệch vị trí roi với simon
	{
		if (_weaponMain->GetFinish() == false) // nếu MorningStar đang đánh
		{
			_weaponMain->SetPosition(this->x, this->y);
			_weaponMain->UpdatePositionFitSimon();

			_weaponMain->Update(dt);

			if (_weaponMain->GetFinish() == true) 
				isAttacking = false;
		} 
		else
		{
			if (_weaponSub != NULL)
			{
				isAttacking = !(SIMON_ANI_SITTING_ATTACKING_END + 1 == _sprite->GetIndex() || SIMON_ANI_STANDING_ATTACKING_END + 1 == _sprite->GetIndex());
			} 
		}
	} 

	if (_weaponSub != NULL && _weaponSub->GetFinish() == false)
	{
		_weaponSub->Update(dt);
	}

	*/

	

}

void Simon::Render(Camera* camera)
{ 
	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
	
	D3DXVECTOR2 pos = camera->Transform(x, y);
	 
	if (trend == -1)
		_sprite->Draw((int)pos.x, (int)pos.y);
	else
		_sprite->DrawFlipX((int)pos.x, (int)pos.y);
	 
	if (_weaponMain->GetFinish()==false)
		_weaponMain->Render(camera); // không cần xét hướng, vì Draw của lớp Weapon đã xét khi vẽ

	if (_weaponSub != NULL && _weaponSub->GetFinish() == false)
		_weaponSub->Render(camera); // không cần xét hướng, vì Draw của lớp Weapon đã xét khi vẽ


	 
} 
 

void Simon::Left()
{
	// (isJumping == true || isAttacking == true)
	//	return;
	trend = -1;
}

void Simon::Right()
{
	//if (isJumping == true || isAttacking == true)
	//	return;
	trend = 1; // quay qua phải
}

void Simon::Go()
{
	if (isAttacking == true /*|| isJumping == true*/)
		return;

	vx = SIMON_WALKING_SPEED * trend;
	isWalking = 1;
	
}

void Simon::Sit()
{
	vx = 0;
	isWalking = 0;

	if (isSitting == false) // nếu trước đó simon chưa ngồi
		y = y + 16; // kéo simon xuống

	isSitting = 1;
}

void Simon::Jump()
{
	if (isJumping == true)
		return;

	


	if (isSitting == true)
		return;
	if (isAttacking == true)
		return;
	

	vy -= SIMON_VJUMP;
	isJumping = true;
}

void Simon::Stop()
{
	if (isAttacking == true)
		return;

	vx = 0;

	//if (vx!=0)
	//	vx -= dt*SIMON_GRAVITY*0.1*trend;
	//if (trend == 1 && vx < 0) 
	//	vx = 0;
	//if (trend == -1 && vx > 0) 
	//	vx = 0;
	// tóm lại là vx = 0 :v


	isWalking = 0;
	if (isSitting == true) // nếu simon đang ngồi
	{
		isSitting = 0; // hủy trạng thái ngồi
		y = y - 18; // kéo simon lên
	}
	
}

void Simon::SetHeartCollect(int h)
{
	HeartCollect = h;
}

int Simon::GetHeartCollect()
{
	return HeartCollect;
}

void Simon::CollisionWithBrick(vector<LPOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents); // Lấy danh sách các va chạm

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		// nếu ko va chạm thì min_tx,min_ty = 1.0, còn nếu có thì nó trả về thời gian va chạm. 
		//Còn nx,ny là hướng va chạm,  = 0 nếu ko va chạm;

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f; // ny = -1 thì hướng từ trên xuống....

		if (nx != 0)
			vx = 0; // nếu mà nx, ny <>0  thì nó va chạm rồi. mà chạm rồi thì dừng vận tốc cho nó đừng chạy nữa

		if (ny != 0)
		{
			vy = 0;
			isJumping = false; // kết thúc nhảy
		}

		//// Collision logic with Goombas
		//for (UINT i = 0; i < coEventsResult.size(); i++)
		//{
		//	LPCOLLISIONEVENT e = coEventsResult[i];
		//	if (dynamic_cast<Goomba *>(e->obj))
		//	{
		//		Goomba *goomba = dynamic_cast<Goomba *>(e->obj);
		//		// jump on top >> kill Goomba and deflect a bit 
		//		if (e->ny < 0)
		//		{
		//			if (goomba->GetState() != GOOMBA_STATE_DIE)
		//			{
		//				goomba->SetState(GOOMBA_STATE_DIE);
		//				vy = -MARIO_JUMP_DEFLECT_SPEED;
		//			}
		//		}
		//		else if (e->nx != 0)
		//		{
		//			if (untouchable == 0)
		//			{
		//				if (goomba->GetState() != GOOMBA_STATE_DIE)
		//				{
		//					if (level > MARIO_LEVEL_SMALL)
		//					{
		//						level = MARIO_LEVEL_SMALL;
		//						StartUntouchable();
		//					}
		//					else
		//						SetState(MARIO_STATE_DIE);
		//				}
		//			}
		//		}
		//	}
		//}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}

void Simon::Attack(Weapon * w)
{ 
	if (isAttacking == true && dynamic_cast<MorningStar*>(w)!=NULL) // đang tấn công mà là roi thì bỏ qua
		return;

	isAttacking = true; // set trang thái tấn công
	w->Create(this->x, this->y, this->trend); // set vị trí weapon theo simon
}

int Simon::GetLives()
{
	return Lives;
}

void Simon::SetLives(int l)
{
	Lives = l;
}

int Simon::GetScore()
{
	return score;
}

void Simon::SetScore(int s)
{
	score = s;
}

bool Simon::isCollisionWithItem(Item * objItem)
{ 
	if (objItem->GetFinish() == true) 
		return false; 

	float l, t, r, b;
	float l1, t1, r1, b1;
	this->GetBoundingBox(l, t, r, b);  // lấy BBOX của simon

	objItem->GetBoundingBox(l1, t1, r1, b1);
	if (Game::GetInstance()->AABBCheck(l, t, r, b, l1, t1, r1, b1) == true)
	{
		return true; // check with AABB
	}


	vector<LPOBJECT> listObj;
	listObj.clear();

	listObj.push_back(objItem); // thêm object Item này để kt

	vector<LPCOLLISIONEVENT> coEvents; 

	coEvents.clear();
	CalcPotentialCollisions(&listObj, coEvents); // Lấy danh sách các va chạm

	int countCollision = (int)coEvents.size();

	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];

	return (countCollision > 0); 
}
