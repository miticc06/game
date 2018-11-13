#include "Brick.h"
 

Brick::Brick(int X, int Y, int W, int H, int Model)
{
	switch (Model)
	{
	case 1:
		_texture = TextureManager::GetInstance()->GetTexture(eID::TEX_BRICK_MODEL_1);
		break;
	case 2:
		_texture = TextureManager::GetInstance()->GetTexture(eID::TEX_BRICK_MODEL_2);
		break;
	case 3:
		_texture = TextureManager::GetInstance()->GetTexture(eID::TEX_BRICK_MODEL_3); // loại nhỏ
		break;

	default:
		DebugOut(L"[BRICK] Get Texture that bai! Ko nhan dang duoc Model!\n");
		break;
	}

	type = eID::BRICK; 
	_sprite = new GSprite(_texture, 1000);
	this->x = (float)X;
	this->y = (float)Y;
	this->width = W;
	this->height = H;
}

void Brick::Render(Camera * camera)
{
	D3DXVECTOR2 pos = camera->Transform(x, y);

	 
	for (int i = 0; i < (int)ceil(width / _texture->FrameWidth); i++)
		for (int j = 0; j < (int)ceil(height / _texture->FrameHeight); j++)
			_sprite->Draw( (int) pos.x + i * _texture->FrameWidth, (int)pos.y + j * _texture->FrameHeight);

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
}

void Brick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + (float)ceil(width / _texture->FrameWidth)*_texture->FrameWidth;
	b = y + (float)ceil(height / _texture->FrameHeight)*_texture->FrameHeight;
}