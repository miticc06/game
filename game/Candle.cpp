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
	left = x - 5;
	top = y -5;
	right = x + _texture->FrameWidth+5;
	bottom = y + _texture->FrameHeight+5; //Mở rộng BBOX cho dễ đánh trúng

}

void Candle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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
