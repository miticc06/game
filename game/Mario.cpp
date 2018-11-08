
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"

Mario::Mario() : GameObject()
{
	//level = MARIO_LEVEL_BIG;
	//untouchable = 0;


	//Sprite* _sprite = SpritesManager::GetInstance()->getSprite(eID::MARIO); // get texture của eid 
	// 

	////_animations[MARIO_ANI_BIG_IDLE_RIGHT] = new Animation(12, 13);


	//_animations[MARIO_ANI_BIG_IDLE_RIGHT] = new Animation(_sprite, 100); // Tạo Animation có texture là _sprite, mỗi frame chạy trong 100
	//_animations[MARIO_ANI_BIG_IDLE_RIGHT]->addFrameRect(eID::MARIO, "10001", NULL);


	//_animations[MARIO_ANI_BIG_IDLE_LEFT] = new Animation(_sprite, 100);
	//_animations[MARIO_ANI_BIG_IDLE_LEFT]->addFrameRect(eID::MARIO, "10011",NULL);
 //

	//_animations[MARIO_ANI_SMALL_IDLE_RIGHT] = new Animation(_sprite, 100);
	//_animations[MARIO_ANI_SMALL_IDLE_RIGHT]->addFrameRect(eID::MARIO, "10021", NULL);


	//_animations[MARIO_ANI_SMALL_IDLE_LEFT] = new Animation(_sprite, 100);
	//_animations[MARIO_ANI_SMALL_IDLE_LEFT]->addFrameRect(eID::MARIO, "10031", NULL);
 //  

	//_animations[MARIO_ANI_BIG_WALKING_RIGHT] = new Animation(_sprite, 100);
	//_animations[MARIO_ANI_BIG_WALKING_RIGHT]->addFrameRect(eID::MARIO, "10001","10002","10003", NULL);
	// 

	//_animations[MARIO_ANI_BIG_WALKING_LEFT] = new Animation(_sprite, 100);
	//_animations[MARIO_ANI_BIG_WALKING_LEFT]->addFrameRect(eID::MARIO, "10011", "10012", "10013", NULL);

	// 
	//_animations[MARIO_ANI_SMALL_WALKING_RIGHT] = new Animation(_sprite, 100);
	//_animations[MARIO_ANI_SMALL_WALKING_RIGHT]->addFrameRect(eID::MARIO, "10021", "10022", "10023", NULL);
	// 

	//_animations[MARIO_ANI_SMALL_WALKING_LEFT] = new Animation(_sprite, 100);
	//_animations[MARIO_ANI_SMALL_WALKING_LEFT]->addFrameRect(eID::MARIO, "10031", "10032", "10033", NULL);


	//_animations[MARIO_ANI_DIE] = new Animation(_sprite, 100);
	//_animations[MARIO_ANI_DIE]->addFrameRect(eID::MARIO, "10099", NULL);

	//   

	// 
	// 



}

void Mario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy = 0;

	// Calculate dx, dy 
	GameObject::Update(dt);
	
	// Simple fall down
	vy += MARIO_GRAVITY*dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	/*if (state!=MARIO_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);
*/
	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// No collision occured, proceed normally
	if (coEvents.size()==0)
	{
		x += dx; 
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx*dx + nx*0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty*dy + ny*0.4f;
		
		if (nx!=0) vx = 0; // nếu mà nx, ny <>0  thì nó va chạm rồi. mà chạm rồi thì dừng vận tốc cho nó đừng chạy nữa
		if (ny!=0) vy = 0; 

		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Goomba *>(e->obj))
			{
				Goomba *goomba = dynamic_cast<Goomba *>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					/*if (goomba->GetState()!= GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}*/
				}
				else if (e->nx != 0)
				{
					if (untouchable==0)
					{
						/*if (goomba->GetState()!=GOOMBA_STATE_DIE)
						{
							if (level > MARIO_LEVEL_SMALL)
							{
								level = MARIO_LEVEL_SMALL;
								StartUntouchable();
							}
							else 
								SetState(MARIO_STATE_DIE);
						}*/
					}
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Mario::Render()
{
	/*int ani;
	if (state == MARIO_STATE_DIE)
		ani = MARIO_ANI_DIE;
	else
	if (level == MARIO_LEVEL_BIG)
	{
		if (vx == 0)
		{
			if (nx>0) ani = MARIO_ANI_BIG_IDLE_RIGHT;
			else ani = MARIO_ANI_BIG_IDLE_LEFT;
		}
		else if (vx > 0) 
			ani = MARIO_ANI_BIG_WALKING_RIGHT; 
		else ani = MARIO_ANI_BIG_WALKING_LEFT;
	}
	else if (level == MARIO_LEVEL_SMALL)
	{
		if (vx == 0)
		{
			if (nx>0) ani = MARIO_ANI_SMALL_IDLE_RIGHT;
			else ani = MARIO_ANI_SMALL_IDLE_LEFT;
		}
		else if (vx > 0)
			ani = MARIO_ANI_SMALL_WALKING_RIGHT;
		else ani = MARIO_ANI_SMALL_WALKING_LEFT;
	}

	int alpha = 255;
	if (untouchable) alpha = 128;
	_animations[ani]->Render(x, y, alpha);

	RenderBoundingBox();*/
}

void Mario::SetState(int state)
{
	//GameObject::SetState(state);
/*
	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		vx = MARIO_WALKING_SPEED;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT: 
		vx = -MARIO_WALKING_SPEED;
		nx = -1;
		break;
	case MARIO_STATE_JUMP: 
		vy = -MARIO_JUMP_SPEED_Y;

	case MARIO_STATE_IDLE: 
		vx = 0;
		break;
	case MARIO_STATE_DIE:
		vy = -MARIO_DIE_DEFLECT_SPEED;
		break;
	}*/
}

void Mario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y; 

	if (level==MARIO_LEVEL_BIG)
	{
		right = x + MARIO_BIG_BBOX_WIDTH;
		bottom = y + MARIO_BIG_BBOX_HEIGHT;
	}
	else
	{
		right = x + MARIO_SMALL_BBOX_WIDTH;
		bottom = y + MARIO_SMALL_BBOX_HEIGHT;
	}
}

