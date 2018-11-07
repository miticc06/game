#include "Item.h"



Item::Item()
{
	vx = 0;
	vy = 0;
	TimeDisplayed = 0;

}


Item::~Item()
{
	SAFE_DELETE(_sprite);
	SAFE_DELETE(_texture);

}

void Item::Update(DWORD dt, vector<LPOBJECT> *listObject)
{
}

void Item::Render(Camera * camera)
{

	D3DXVECTOR2 pos = camera->Transform(x, y);

	_sprite->Draw(pos.x, pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
}
 

bool Item::GetFinish()
{
	return isFinish;
}
