#include "Brick.h"

Brick::Brick()
{
	_animations[0] = AnimationsManager::GetInstance()->Get(601);

 
}

void Brick::Render()
{
	_animations[0]->Render(x, y);
	//RenderBoundingBox();
}

void Brick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}