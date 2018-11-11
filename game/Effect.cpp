#include "Effect.h"



Effect::Effect()
{
	isFinish = 0;
}


Effect::~Effect()
{
	SAFE_DELETE(_sprite);
}

void Effect::Render(Camera * camera)
{
	D3DXVECTOR2 pos = camera->Transform(x, y);
	_sprite->Draw(pos.x, pos.y); 

}

void Effect::Update(DWORD dt)
{ 
	_sprite->Update(dt);
}

bool Effect::GetFinish()
{
	return isFinish;
}

void Effect::SetFinish(int b)
{
	isFinish = b;
}
