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

void Item::Update(DWORD dt, vector<GameObject*> *listObject)
{
}

void Item::Render(Camera * camera)
{

	D3DXVECTOR2 pos = camera->Transform(x, y);

	_sprite->Draw(pos.x, pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
}

void Item::SetPosition(float X, float Y)
{
	this->x = X;
	this->y = Y;
}

eID Item::GetType()
{
	return type;
}

void Item::RenderBoundingBox(Camera * camera)
{ 
	RECT rect; 
	float l, t, r, b; 
	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t; 
	D3DXVECTOR2 pos = camera->Transform(l, t); 
	LPDIRECT3DTEXTURE9  _Texture = DebugRenderBBOX::GetInstance()->GetTexture();
	Game::GetInstance()->Draw(pos.x, pos.y, _Texture, rect.left, rect.top, rect.right, rect.bottom, 100);

}

bool Item::GetFinish()
{
	return isFinish;
}
