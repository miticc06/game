#include "StairBottom.h"

 


StairBottom::StairBottom(int X, int Y, int Direction)
{
	x = X-25;
	y = Y;
	width = 50;
	height = 50;
	direction = Direction;
	type = eType::STAIR_BOTTOM;


	y -= width;
}

StairBottom::~StairBottom()
{
}

void StairBottom::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	right = x + width;
	top = y;
	bottom = y + width;

	 
}

void StairBottom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void StairBottom::Render(Camera * camera)
{
	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
}
