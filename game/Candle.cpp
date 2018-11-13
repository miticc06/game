#include "Candle.h"


  
Candle::~Candle()
{
}
 

Candle::Candle(int X, int Y)
{
	_texture = TextureManager::GetInstance()->GetTexture(eID::CANDLE);
	_sprite = new GSprite(_texture, 100);
	this->x = (float)X;
	this->y = (float)Y;
	type = eID::CANDLE;
	Health = 1;
}



void Candle::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + _texture->FrameWidth;
	bottom = y + _texture->FrameHeight;

}

void Candle::Update(DWORD dt, vector<LPOBJECT>* coObjects)
{
	_sprite->Update(dt); // update animation
}

void Candle::Render(Camera * camera)
{
	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);

	D3DXVECTOR2 pos = camera->Transform(x, y);
	_sprite->Draw((int)pos.x, (int)pos.y);
}
