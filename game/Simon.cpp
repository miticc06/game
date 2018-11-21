#include "Simon.h"
 

Simon::Simon()
{
 	_texture = TextureManager::GetInstance()->GetTexture(eType::SIMON);
	_sprite = new GSprite(_texture, 250);
	type = eType::SIMON;

	isWalking = 0;
	isJumping = 0;
	isSitting = 0;
	isAttacking = 0;
	isProcessingOnStair = 0;// ko phải đang xử lí
	isOnStair = 0;

	Health = SIMON_DEFAULT_HEALTH; // simon dính 16 phát là chết
	Lives = 3; // có 5 mạng sống
	HeartCollect = SIMON_DEFAULT_HEARTCOLLECT;
	score = 0;
	


	isAttacking = 0;
	isJumping = 0;
 	isSitting = 0;
	isWalking = 0;

	isAutoGoX = 0;
	isHurting = 0;

	vx = 0;
	vy = 0; 
	isProcessingOnStair = 0;
	DoCaoDiDuoc = 0;
	isFreeze = 0;
	TimeFreeze = 0;
	direction = 1;


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
		right = x + SIMON_BBOX_WIDTH - 17+5-3;
		bottom = y + SIMON_BBOX_SITTING_HEIGHT -3;
	}
	else
	{ 
		left = x +15;
		top = y -1 ;
		right = x + SIMON_BBOX_WIDTH - 17+5-3;
		bottom = y + SIMON_BBOX_HEIGHT - 3;
	}
 	
}

void Simon::Update(DWORD dt, Camera* camera, vector<LPGAMEOBJECT>* coObjects)
{ 
	 
	if (x < camera->GetBoundaryLeft()-16)
		x = camera->GetBoundaryLeft()-16;
	if (x + SIMON_BBOX_WIDTH > camera->GetBoundaryRight() + Window_Width)
		x = (float)(camera->GetBoundaryRight() + Window_Width - SIMON_BBOX_WIDTH);
	/* Không cho lọt khỏi camera */


#pragma region Update về sprite
	 
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
				isAttacking = !(SIMON_ANI_SITTING_ATTACKING_END == index || SIMON_ANI_STANDING_ATTACKING_END == index || 
					SIMON_ANI_STAIR_UP_ATTACKING_END==index || SIMON_ANI_STAIR_DOWN_ATTACKING_END==index);
			}
		}
	}

	if (_weaponSub != NULL && _weaponSub->GetFinish() == false)
	{
		_weaponSub->Update(dt, coObjects);
	}


	if (isOnStair)
	{  
		if (isAttacking == true) // tấn công
		{
			if (directionY == -1) // đang đi lên
			{
				if (index < SIMON_ANI_STAIR_UP_ATTACKING_BEGIN || index >= SIMON_ANI_STAIR_UP_ATTACKING_END)
				{
					_sprite->SelectIndex(SIMON_ANI_STAIR_UP_ATTACKING_BEGIN);
				}
				else
				{
					//cập nhật frame mới
					_sprite->Update(dt); // dt này được cập nhật khi gọi update; 
				}
			}
			else
			{
				if (index < SIMON_ANI_STAIR_DOWN_ATTACKING_BEGIN || index >= SIMON_ANI_STAIR_DOWN_ATTACKING_END)
				{
					_sprite->SelectIndex(SIMON_ANI_STAIR_DOWN_ATTACKING_BEGIN);
				}
				else
				{
					//cập nhật frame mới
					_sprite->Update(dt); // dt này được cập nhật khi gọi update; 
				}
			}


			
		}
		else
		{
			if (isWalking == true)
			{
				if (isProcessingOnStair == 1) // nếu ở giai đoạn bước chân thì set frame 12
				{
					if (vy < 0) // ddi len
						_sprite->SelectIndex(SIMON_ANI_STAIR_GO_UP_BEGIN);
					else
						_sprite->SelectIndex(SIMON_ANI_STAIR_GO_DOWN_BEGIN);
				}


				if (isProcessingOnStair == 2) // nếu ở giai đoạn bước chân trụ thì set frame 13
				{
					if (vy < 0) // ddi len
						_sprite->SelectIndex(SIMON_ANI_STAIR_GO_UP_END);
					else
						_sprite->SelectIndex(SIMON_ANI_STAIR_GO_DOWN_END);

				}
				 
				float kk = 8.0f;
				 
				DoCaoDiDuoc = DoCaoDiDuoc + abs(vy) * 16.0f;

				if (DoCaoDiDuoc >= 8.0f && isProcessingOnStair == 1)
					isProcessingOnStair++;

				if (DoCaoDiDuoc >= 16)
				{ 
					isProcessingOnStair++; 

					/* fix lỗi mỗi lần đi vượt quá 16px */
					if (direction == 1 && directionY == -1) // đi lên bên phải
					{
						x -= (DoCaoDiDuoc - 16.0f);
						y += (DoCaoDiDuoc - 16.0f);
					}
					if (direction == -1 && directionY == -1) // đi lên bên trái
					{
						x += (DoCaoDiDuoc - 16.0f);
						y += (DoCaoDiDuoc - 16.0f);
					}

					if (direction == 1 && directionY == 1) // đi xuống bên phải
					{
						x -= (DoCaoDiDuoc - 16.0f);
						y -= (DoCaoDiDuoc - 16.0f);
					}
					if (direction == -1 && directionY == 1) // đi xuống bên trái
					{
						x += (DoCaoDiDuoc - 16.0f);
						y -= (DoCaoDiDuoc - 16.0f);
					}
					DoCaoDiDuoc = 0; 
				}
				//	DebugOut(L"DoCaoDiDuoc = %f . dy = %f . y = %f\n", DoCaoDiDuoc, dy, y);

			}
			else
			{
				if (this->directionY == -1) // ddang di len
					_sprite->SelectIndex(SIMON_ANI_STAIR_STANDING_UP);
				else
					_sprite->SelectIndex(SIMON_ANI_STAIR_STANDING_DOWN);
			} 
		}
	
	//	DebugOut(L"_sprite index = %d \n", _sprite->GetIndex());

	}
	else
	{
		if (isHurting)
		{
			_sprite->SelectIndex(SIMON_ANI_HURTING);
		}
		else
		{

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
					if (index < SIMON_ANI_STANDING_ATTACKING_BEGIN || index >= SIMON_ANI_STANDING_ATTACKING_END)
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


		}
	}
#pragma endregion

	/* Update về sprite */

	  

	GameObject::Update(dt);   



	
	if (isOnStair == false) // ko trên cầu thang thì mới có trọng lực
		vy += SIMON_GRAVITY * dt;// Simple fall down
	else
	{
		this->dt = dt;
		dx = vx * 16;
		dy = vy * 16;
		 
	} 


	if (isJumping && isWalking)
	{
		dx = vx * dt *1.5f; 
	}
		
	if (isOnStair == false)
	{
		if (isAutoGoX == false)
 			CollisionWithBrick(coObjects); // check Collision and update x, y for simon
		else
		{
			x += dx;
		}
	}
	 



	if (isOnStair == true)
		CollisionIsOnStair(coObjects);
		 
	 
	 


	_weaponMain->SetPosition(this->x, this->y);
	_weaponMain->SetSpeed(vx, vy); // set vận tốc để kt va chạm
	_weaponMain->UpdatePositionFitSimon();

	if (isProcessingOnStair == 3)
	{
		isProcessingOnStair = 0; 
		vx = 0;
		vy = 0;
		isWalking = false;
	}



	if (isAutoGoX == true)
	{
		if (abs(x - AutoGoX_Backup_X) >= AutoGoX_Dx)
		{
			x = x - (abs(x - AutoGoX_Backup_X) - AutoGoX_Dx);
			RestoreBackupAutoGoX();
			isAutoGoX = false;

			DebugOut(L"[SIMON] end auto go X\n"); 
		}
	}

}

void Simon::Render(Camera* camera)
{ 
	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
	
	D3DXVECTOR2 pos = camera->Transform(x, y);
	 
	int alpha = 255;
	if (untouchable) 
		alpha = 128;

	if (this->GetFreeze() == true)
	{
		if (direction == -1)
			_sprite->DrawRandomColor((int)pos.x, (int)pos.y, alpha);
		else
			_sprite->DrawRandomColorFlipX((int)pos.x, (int)pos.y, alpha);
	}
	else
	{
		if (direction == -1)
			_sprite->Draw((int)pos.x, (int)pos.y, alpha);
		else
			_sprite->DrawFlipX((int)pos.x, (int)pos.y, alpha);
	}



	if (_weaponMain->GetFinish()==false)
		_weaponMain->Render(camera); // không cần xét hướng, vì Draw của lớp Weapon đã xét khi vẽ

	if (_weaponSub != NULL && _weaponSub->GetFinish() == false)
		_weaponSub->Render(camera); // không cần xét hướng, vì Draw của lớp Weapon đã xét khi vẽ
	 
}
 
void Simon::Left()
{
	if (isOnStair == true)
		return;

	// (isJumping == true || isAttacking == true)
	//	return;
	direction = -1;
}

void Simon::Right()
{
	if (isOnStair == true)
		return;
	//if (isJumping == true || isAttacking == true)
	//	return;
	direction = 1; // quay qua phải
}

void Simon::Go()
{
	if (isOnStair == true)
	{
		//isWalking = 1;
		return;
	}

	if (isAttacking == true /*|| isJumping == true*/)
		return;

	vx = SIMON_WALKING_SPEED * direction;
	isWalking = 1;
	
}

void Simon::Sit()
{

	if (isOnStair == true)
		return;

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

	if (isOnStair == true)
		return;


	if (isSitting == true)
		return;
	if (isAttacking == true)
		return;
	
	if (isHurting)
		return;

	vy -= SIMON_VJUMP;
	isJumping = true;
}

void Simon::Stop()
{
	if (isAttacking == true)
		return;

	if (isOnStair)
		return;

	if (isHurting)
		return;

	vx = 0;
	//DebugOut(L"[STOP] Set vx = %f \n", vx);

	//if (vx!=0)
	//	vx -= dt*SIMON_GRAVITY*0.1*direction;
	//if (direction == 1 && vx < 0) 
	//	vx = 0;
	//if (direction == -1 && vx > 0) 
	//	vx = 0;
	// tóm lại là vx = 0 :v


	isWalking = 0;
	if (isSitting == true) // nếu simon đang ngồi
	{
		isSitting = 0; // hủy trạng thái ngồi
		y = y - 18; // kéo simon lên
	}
	
}

void Simon::SetHurt(LPCOLLISIONEVENT e)
{
	if (isHurting == true)
		return;
	if (e->nx == 0 && e->ny == 0) // ko có va chạm
		return;

	isWalking = 0;
	isAttacking = 0;
	isJumping = 0;
	if (isSitting == true) // nếu simon đang ngồi
	{
		isSitting = 0; // hủy trạng thái ngồi
		y = y - 18; // kéo simon lên
	}
	
	if (!isOnStair)
	{
		if (e->nx != 0)
		{
			vx = SIMON_WALKING_SPEED * e->nx * 2;
			vy = -SIMON_VJUMP;
			isHurting = 1;
			//DebugOut(L"[SetHurt] Set vx = %f \n", vx);
		}

		if (e->ny != 0)
		{
			vy = -SIMON_VJUMP;
			isHurting = 1;
			//DebugOut(L"[SetHurt] Set vy = %f \n", vy);
		}
	}
	else
	{
		//vx = 0;
		//vy = 0;
		isWalking = 1;
		//isHurting = 1;
	}

	StartUntouchable(); // không cho các object đụng tiếp

	_weaponMain->SetFinish(true);
	SubHealth(2); // chạm enemy -2 máu
	Sound::GetInstance()->Play(eSound::soundHurting);
}

void Simon::SetHeartCollect(int h)
{
	HeartCollect = h;
}

int Simon::GetHeartCollect()
{
	return HeartCollect;
}

void Simon::CollisionWithBrick(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	 
	vector<LPGAMEOBJECT> list_Brick;
	list_Brick.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->GetType() == eType::BRICK)
			list_Brick.push_back(coObjects->at(i));

	
	CalcPotentialCollisions(&list_Brick, coEvents); // Lấy danh sách các va chạm 
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
			;//	vx = 0; 

		if (ny != 0)
		{
			vy = 0;
			isJumping = false; // kết thúc nhảy
		}
		 
		if (nx != 0 || ny != 0)
		{
			isHurting = 0; 
		}

	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}

void Simon::CollisionIsOnStair(vector<LPGAMEOBJECT> *coObjects)
{
	if (directionY == 1) // đang đi xuống
	{
		int CountCollisionBottom = 0;
		vector<LPGAMEOBJECT> listobj;
		listobj.clear();
		for (UINT i = 0; i < (*coObjects).size(); i++)
			if ((*coObjects)[i]->GetType() == eType::STAIR_BOTTOM) // nếu là object ở dưới
			{
				if (this->isCollitionObjectWithObject((*coObjects)[i]))
				{
					CountCollisionBottom++;
					break;
				}
			}

		if (CountCollisionBottom > 0) // có va chạm với bottom
		{
			vector<LPCOLLISIONEVENT> coEvents;
			vector<LPCOLLISIONEVENT> coEventsResult;
			coEvents.clear();
			vector<LPGAMEOBJECT> list_Brick;
			list_Brick.clear();
			for (UINT i = 0; i < coObjects->size(); i++)
				if (coObjects->at(i)->GetType() == eType::BRICK)
					list_Brick.push_back(coObjects->at(i));
			CalcPotentialCollisions(&list_Brick, coEvents);
			if (coEvents.size() == 0)
			{
				x += dx;
				y += dy;
			}
			else
			{
				float min_tx, min_ty, nx = 0, ny;

				FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
				x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.4f;
				if (nx != 0 || ny != 0)
				{
					vx = 0;
					vy = 0;
					isOnStair = false; // kết thúc việc đang trên cầu thang
					isWalking = false;
					isProcessingOnStair = 0;
				}
			}

			for (UINT i = 0; i < coEvents.size(); i++)
				delete coEvents[i];

			return; // ko cần xét tiếp
		}

	}

	 
	if (directionY == -1) // đang đi lên
	{
		vector<LPGAMEOBJECT> listobj;
		int CountCollisionTop = 0;
		listobj.clear();
		for (UINT i = 0; i < (*coObjects).size(); i++)
			if ((*coObjects)[i]->GetType() == eType::STAIR_TOP) // nếu là object ở trên
			{
				if (this->isCollitionObjectWithObject((*coObjects)[i])) // có va chạm với top stair
				{
					CountCollisionTop++;
					break;
				}
			}

		if (CountCollisionTop > 0) // có va chạm với top, và nó đang đi lên
		{ 
			float backupVy = vy;

			y = y - 50; // kéo simon lên cao, để tạo va chạm giả xuống mặt đất. tính thời gian tiếp đất
			vy = 15; // vận tốc kéo xuống lớn
			dy = vy * dt; // cập nhật lại dy

			 
			vector<LPCOLLISIONEVENT> coEvents;
			vector<LPCOLLISIONEVENT> coEventsResult;
			coEvents.clear();
			vector<LPGAMEOBJECT> list_Brick;
			list_Brick.clear();

			for (UINT i = 0; i < coObjects->size(); i++)
				if (coObjects->at(i)->GetType() == eType::BRICK)
					list_Brick.push_back(coObjects->at(i));

			CalcPotentialCollisions(&list_Brick, coEvents);
			if (coEvents.size() == 0)
			{
				x += dx;
				y += dy;
			}
			else
			{
				float min_tx, min_ty, nx = 0, ny;

				FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
				x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.4f;
				if (nx != 0 || ny != 0)
				{
					vx = 0;
					vy = 0;
					isOnStair = false; // kết thúc việc đang trên cầu thang
					isWalking = false;
					isProcessingOnStair = 0;
				}
			}

			for (UINT i = 0; i < coEvents.size(); i++)
				delete coEvents[i];
			
			vy = backupVy;
			dy = vy * dt; // cập nhật lại dy

			return; // ko cần xét tiếp
		}

	}

	 // nếu không đụng top và bot thì di chuyển bt
	x += dx;
	y += dy; 

}


bool Simon::isCollisionWithItem(Item * objItem)
{
	if (objItem->GetFinish() == true)
		return false;

	float l, t, r, b;
	float l1, t1, r1, b1;
	this->GetBoundingBox(l, t, r, b);  // lấy BBOX của simon

	objItem->GetBoundingBox(l1, t1, r1, b1);
	if (Game::GetInstance()->checkAABB(l, t, r, b, l1, t1, r1, b1) == true)
	{
		return true; // check with AABB
	}

	return isCollitionObjectWithObject(objItem);
}


void Simon::Attack(Weapon * w)
{ 
	if (isAttacking == true && dynamic_cast<MorningStar*>(w)!=NULL) // đang tấn công mà là roi thì bỏ qua
		return;

	isAttacking = true; // set trang thái tấn công
	w->Create(this->x, this->y, this->direction); // set vị trí weapon theo simon
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

bool Simon::GetFreeze()
{
	return isFreeze;
}

void Simon::SetFreeze(int f)
{
	isFreeze = f;
	TimeFreeze = 0; // thời gian đã đóng băng
}

void Simon::UpdateFreeze(DWORD dt)
{
	if (TimeFreeze + dt >= TIME_FREEZE_MAX)
	{
		SetFreeze(false); // kết thúc đóng băng
	}
	else
		TimeFreeze += dt;
}

void Simon::StartUntouchable()
{
	untouchable = true; 
	untouchable_start = GetTickCount();
}
 

void Simon::SetAutoGoX(int DirectionGo, int directionAfterGo, float Dx, float Speed)
{
	if (isAutoGoX == true)
		return;

	isAutoGoX = true;// chưa vào chế độ autoGo thì set

	AutoGoX_Backup_X = x;

	//Backup trạng thái
	isWalking_Backup = isWalking;
	isJumping_Backup = isJumping;
	isSitting_Backup = isSitting;
	isAttacking_Backup = isAttacking;
	isOnStair_Backup = isOnStair;
	isProcessingOnStair_Backup = isProcessingOnStair;
	directionStair_Backup = directionStair;
	directionY_Backup = directionY;

	AutoGoX_Dx = Dx;
	AutoGoX_Speed = Speed;
	AutoGoX_DirectionGo = DirectionGo;
	this->directionAfterGo = directionAfterGo;


	direction = DirectionGo;
 	vx = Speed * DirectionGo;
	isWalking = 1;
	isJumping = 0;
	isSitting = 0;
	isAttacking = 0;
	isOnStair = 0;
	isProcessingOnStair = 0;
}

void Simon::RestoreBackupAutoGoX()
{
	isWalking = isWalking_Backup;
	isJumping = isJumping_Backup;
	isSitting = isSitting_Backup;
	isAttacking = isAttacking_Backup;
	isOnStair = isOnStair_Backup;
	isProcessingOnStair = isProcessingOnStair_Backup;
	directionStair = directionStair_Backup;
	directionY = directionY_Backup;
	 
	direction = directionAfterGo; // set hướng sau khi đi

	isWalking = 0; // tắt trạng thái đang đi
	isAutoGoX = 0; // tắt trạng thái auto
	
	vx = 0;
	vy = 0;
	// đi xong thì cho simon đứng yên
}
 

bool Simon::LoseLife()
{
	if (Lives - 1 < 0)
		return false;
	Health = SIMON_DEFAULT_HEALTH;
	Lives = Lives - 1;
	HeartCollect = SIMON_DEFAULT_HEARTCOLLECT;
	SAFE_DELETE(_weaponMain);
	SAFE_DELETE(_weaponSub);
	_weaponMain = new MorningStar();
	_weaponSub = NULL; 

	isAttacking = 0;
	isJumping = 0;
	isFreeze = 0;
	isSitting = 0;
	isWalking = 0;

	isAutoGoX = 0;
	isHurting = 0;

	vx = 0;
	vy = 0;

	isOnStair = 0;
	isProcessingOnStair = 0;
	DoCaoDiDuoc = 0;
	isFreeze = 0;
	TimeFreeze = 0;
	direction = 1;

	x = PositionBackup.x;
	y = PositionBackup.y;

	return true;
}

void Simon::SetPositionBackup(float X, float Y)
{
	PositionBackup = D3DXVECTOR2(X, Y);
}
