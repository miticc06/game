#include "Brick.h"
 



Brick::Brick(int X, int Y, int W, int H, int Model)
{
	model = Model;
	switch (Model)
	{
	case BRICK_MODEL_1:
		_texture = TextureManager::GetInstance()->GetTexture(eType::TEX_BRICK_MODEL_1); // loại màn 1
		break;
	case BRICK_MODEL_2:
		_texture = TextureManager::GetInstance()->GetTexture(eType::TEX_BRICK_MODEL_2); // loại màn 2
		break;
	case BRICK_MODEL_3:
		_texture = TextureManager::GetInstance()->GetTexture(eType::TEX_BRICK_MODEL_3); // loại nhỏ 16px
		break;
	case BRICK_MODEL_TRANSPARENT:
		_texture = TextureManager::GetInstance()->GetTexture(eType::TEX_BRICK_TRANSPARENT);// loại trong suốt 
		break;
	case BRICK_MODEL_3_3_32:
		_texture = TextureManager::GetInstance()->GetTexture(eType::TEX_BRICK_MODEL_3_3_32);// loại 3 ô nhỏ - 32px 
		break;
	case BRICK_MODEL_3_4_32:
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
	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);

	if (model == BRICK_MODEL_TRANSPARENT)
		return;


	//return;

	D3DXVECTOR2 pos = camera->Transform(x, y);
 
	for (int i = 0; i < (int)ceil(width / _texture->FrameWidth); i++)
		for (int j = 0; j < (int)ceil(height / _texture->FrameHeight); j++)
			_sprite->Draw((int)pos.x + i * _texture->FrameWidth, (int)pos.y + j * _texture->FrameHeight);
 
	//int vtd = 0;
	//if (x < camera->GetXCam())
	//	vtd =  (camera->GetXCam() - x) / _texture->FrameWidth;

	//int vtc = (int)ceil(width / _texture->FrameWidth);// min((int)ceil(width / _texture->FrameWidth), vtd + camera->GetWidth() / _texture->FrameWidth);


	//for (int i = vtd; i < vtc; i++)
	//	for (int j = 0; j < (int)ceil(height / _texture->FrameHeight); j++)
	//		_sprite->Draw((int)pos.x + i * _texture->FrameWidth, (int)pos.y + j * _texture->FrameHeight);
 //
	//for (int i = 0; i < (int)ceil(width / _texture->FrameWidth); i++)
	//	for (int j = 0; j < (int)ceil(height / _texture->FrameHeight); j++)
	//		_sprite->Draw((int)pos.x + i * _texture->FrameWidth, (int)pos.y + j * _texture->FrameHeight);
 // 
	
}

void Brick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + (float)ceil(width / _texture->FrameWidth)*_texture->FrameWidth;
	b = y + (float)ceil(height / _texture->FrameHeight)*_texture->FrameHeight;
}

int Brick::GetModel()
{
	return model;
}
