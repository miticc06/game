#include "StairTop.h"

 

StairTop::StairTop(int X, int Y, int Trend)
{ 
	x = X-25;
	y = Y;
	width = 50;
	height = 50;
	direction = Trend;
	type = eID::STAIR_TOP;

	y -= width;

}

StairTop::~StairTop()
{
}

void StairTop::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{

	left = x;
	right = x + width;
	top = y;
	bottom = y + width;

}

void StairTop::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void StairTop::Render(Camera * camera)
{
	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
}
