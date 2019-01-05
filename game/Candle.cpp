#include "Candle.h"


  
Candle::~Candle()
{
}
 

Candle::Candle(float X, float Y)
{
	texture = TextureManager::GetInstance()->GetTexture(eType::CANDLE);
	sprite = new GSprite(texture, 100);
	this->x = X;
	this->y = Y;
	type = eType::CANDLE;
	Health = 1;
}



void Candle::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x - 5;
	top = y - 5;
	right = x + texture->GetFrameWidth() + 5;
	bottom = y + texture->GetFrameHeight() + 5; //Mở rộng BBOX cho dễ đánh trúng

}

void Candle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	sprite->Update(dt); // update animation
}

void Candle::Render(Camera * camera)
{
	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);

	D3DXVECTOR2 pos = camera->Transform(x, y);
	sprite->Draw(pos.x, pos.y);
}
