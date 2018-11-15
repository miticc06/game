#include "ExitStair.h"

 

ExitStair::ExitStair(int X, int Y, int W, int H)
{
	x = X;
	y = Y;
	width =	W;
	height = H;

	type = eID::STAIR_EXIT;
	trend = -1;
}

ExitStair::~ExitStair()
{
}

void ExitStair::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	right = x + width;
	top = y;
	bottom = y + height;
}

void ExitStair::Update(DWORD dt, vector<LPOBJECT>* coObjects)
{
}

void ExitStair::Render(Camera * camera)
{
	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);

}
