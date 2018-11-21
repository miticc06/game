#include "StopWatch.h"



StopWatch::StopWatch()
{
	type = eType::STOPWATCH;

	_texture = TextureManager::GetInstance()->GetTexture(eType::STOPWATCH);
	_sprite = new GSprite(_texture, 100);
 
 	isFinish = true;
}



StopWatch::~StopWatch()
{
}

void StopWatch::Create(float simonX, float simonY, int simonDirection)
{
	TimeSpent = 0;
	isFinish = false;

}

void StopWatch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isFinish)
		return;
	TimeSpent += dt;
	if (TimeSpent >= 5000) // hoạt động trong 5s
	{
		TimeSpent = 0;
		isFinish = true;
	}
}

void StopWatch::Render(Camera * camera)
{
}

bool StopWatch::isCollision(GameObject * obj)
{
	return false;
}

void StopWatch::RenderIcon(int X, int Y)
{
	_sprite->Draw(X, Y);
}

void StopWatch::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
}
