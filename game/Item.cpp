#include "Item.h"



Item::Item()
{ 
	TimeDisplayed = 0;

}


Item::~Item()
{
	 
}

void Item::Update(DWORD dt, vector<LPOBJECT> *listObject)
{
}

void Item::Render(Camera * camera)
{
	if (isFinish == true)
		return;

	D3DXVECTOR2 pos = camera->Transform(x, y);

	_sprite->Draw(pos.x, pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
}
 



bool Item::GetFinish()
{
	return isFinish;
}

void Item::SetFinish(bool b)
{
	isFinish = b;
}
