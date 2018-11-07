#include "Goomba.h"

void Goomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + GOOMBA_BBOX_WIDTH;

	//if (state == GOOMBA_STATE_DIE)
	//	bottom = y + GOOMBA_BBOX_HEIGHT_DIE;
	//else 	
	//	bottom = y + GOOMBA_BBOX_HEIGHT;
}

void Goomba::Update(DWORD dt, vector<LPOBJECT> *coObjects)
{
	GameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	x += dx;
	y += dy;

	if (vx < 0 && x < 0)
	{
		x = 0;
		vx = -vx;
	}

	if (vx > 0 && x > 290)
	{
		x = 290;
		vx = -vx;
	}
}

void Goomba::Render()
{
	//int ani = GOOMBA_ANI_WALKING;
	//if (state == GOOMBA_STATE_DIE) {
	//	ani = GOOMBA_ANI_DIE;
	//}

	//_animations[ani]->Render(x,y);
	//RenderBoundingBox();
}

void Goomba::SetState(int state)
{
	//GameObject::SetState(state);
	switch (state)
	{
		case GOOMBA_STATE_DIE:
			y += GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE + 1;
			vx = 0;
			vy = 0;
			break;
		case GOOMBA_STATE_WALKING: 
			vx = -GOOMBA_WALKING_SPEED;
	}

}

Goomba::Goomba()
{
	//_animations[GOOMBA_ANI_WALKING] = AnimationsManager::GetInstance()->Get(701);
	//_animations[GOOMBA_ANI_DIE] = AnimationsManager::GetInstance()->Get(702);
	 
}
