#include "Torch.h"


 

Torch::Torch(int X, int Y)
{
	_texture = new GTexture("Resources\\ground\\0.png", 2, 1, 2, 0);
	_sprite = new GSprite(_texture, 100);
	this->x = X;
	this->y = Y;
	type = eID::TORCH;
	Health = 1; 
}

Torch::~Torch()
{

}

void Torch::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + _texture->FrameWidth;
	bottom = y + _texture->FrameHeight;

}

void Torch::Update(DWORD dt, vector<LPOBJECT>* coObjects)
{
	_sprite->Update(dt); // update animation
}

void Torch::Render(Camera * camera)
{ 

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);

	D3DXVECTOR2 pos = camera->Transform(x, y); 
	_sprite->Draw(pos.x, pos.y); 


}
