#include "Stair.h"

 
 
Stair::Stair(int X, int Y, int W, int H, int T, int Trend)
{
	x = X;
	y = Y;
	width = 25;
	height = H;
	t = T;
	if (t == 1) // up
		type = eID::STAIR_UP;
	trend = Trend;
}

Stair::~Stair()
{
}

void Stair::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x - width;
	right = x + width;
	top = y;
	bottom = y + height;
}

void Stair::Update(DWORD dt, vector<LPOBJECT>* coObjects)
{
}

void Stair::Render(Camera * camera)
{
	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);

}
