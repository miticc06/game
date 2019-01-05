#include "Torch.h"


 

Torch::Torch(float X, float Y)
{
	texture = TextureManager::GetInstance()->GetTexture(eType::TORCH);
	sprite = new GSprite(texture, 100);
	this->x = X;
	this->y = Y;
	type = eType::TORCH;
	Health = 1; 
}

Torch::~Torch()
{

} 

void Torch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	sprite->Update(dt); // update animation
}

void Torch::Render(Camera * camera)
{ 
	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);

	D3DXVECTOR2 pos = camera->Transform(x, y); 
	sprite->Draw(pos.x, pos.y);


}
