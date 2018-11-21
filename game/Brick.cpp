#include "Brick.h"
 

Brick::Brick(int X, int Y, int W, int H, int Model)
{
	switch (Model)
	{
	case 1:
		_texture = TextureManager::GetInstance()->GetTexture(eType::TEX_BRICK_MODEL_1); // loại màn 1
		break;
	case 2:
		_texture = TextureManager::GetInstance()->GetTexture(eType::TEX_BRICK_MODEL_2); // loại màn 2
		break;
	case 3:
		_texture = TextureManager::GetInstance()->GetTexture(eType::TEX_BRICK_MODEL_3); // loại nhỏ 16px
		break;
	case 4: 
		_texture = TextureManager::GetInstance()->GetTexture(eType::TEX_BRICK_TRANSPARENT);// loại trong suốt 
		break;
	case 5:
		_texture = TextureManager::GetInstance()->GetTexture(eType::TEX_BRICK_MODEL_3_3_32);// loại 3 ô nhỏ - 32px 
		break;
	case 6:
		_texture = TextureManager::GetInstance()->GetTexture(eType::TEX_BRICK_MODEL_3_4_32);// loại đủ 4 ô nhỏ - 32px
		break;
	default:
		DebugOut(L"[BRICK] Get Texture that bai! Ko nhan dang duoc Model!\n");
		break;
	}

	type = eType::BRICK; 
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