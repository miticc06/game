#include "GSprite.h" 

RECT GSprite::GetRectFrame(int index)
{
	RECT res; 
	res.left = (index % _texture->Cols)*(_texture->FrameWidth);
	res.top = (index / _texture->Cols)*(_texture->FrameHeight);
	res.right = res.left + _texture->FrameWidth;
	res.bottom = res.top + _texture->FrameHeight;
	return res;
}
  
GSprite::GSprite(GTexture* texture, DWORD timeAnimation)
{
	_texture = texture;
	_start = 0;
	_end = _texture->Count - 1;
	_timeAni = timeAnimation;
	_index = 0;
	_timeLocal = 0; 

	spriteHandler = Game::GetInstance()->GetSpriteHandler();
}

GSprite::~GSprite()
{

}
 
void GSprite::Next()
{
	_index++;
	if (_index > _end)
		_index = _start;
}

void GSprite::Reset()
{
	_index = _start;
	_timeLocal = 0;
}

void GSprite::ResetTime()
{ 
	_timeLocal = 0; 
}

void GSprite::SelectIndex(int index)
{
	_index = index;
	//_timeLocal = 0;
}

void GSprite::Update(DWORD dt)
{
	_timeLocal += dt;
	if (_timeLocal >= _timeAni)
	{
		_timeLocal -= _timeAni;
		//_timeLocal = 0;
		this->Next();
	}
}

//void GSprite::Draw(int X, int Y, int alpha)
//{
//	this->Draw((float)X, (float)Y, alpha);
//}


void GSprite::Draw(float X, float Y, int alpha)
{ 
	RECT r = GetRectFrame(_index);
	D3DXVECTOR3 p(X, Y, 0);
	spriteHandler->Draw(_texture->Texture, &r, NULL, &p, D3DCOLOR_ARGB(alpha, 255, 255, 255));
} 

void GSprite::DrawRandomColor(float X, float Y, int alpha)
{
	RECT r = GetRectFrame(_index);

	int RR, GG, BB;
	RR = rand() % 256;
	GG = rand() % 256;
	BB = rand() % 256;
 
	D3DXVECTOR3 p((float)X, (float)Y, 0);
	spriteHandler->Draw(_texture->Texture, &r, NULL, &p, D3DCOLOR_ARGB(alpha, RR, GG, BB));
}

void GSprite::DrawRandomColorFlipX(float x, float y, int alpha)
{
	D3DXMATRIX oldMt;
	spriteHandler->GetTransform(&oldMt);

	D3DXMATRIX newMt;
	D3DXVECTOR2 top_left = D3DXVECTOR2((float)x, (float)y);
	D3DXVECTOR2 rotate = D3DXVECTOR2(-1.0f, 1.0f);
	D3DXMatrixTransformation2D(&newMt, &top_left, 0.0f, &rotate, NULL, 0.0f, NULL);

	D3DXMATRIX finalMt = newMt * oldMt;
	spriteHandler->SetTransform(&finalMt);

	x -= _texture->FrameWidth;

	this->DrawRandomColor(x, y, alpha);

	spriteHandler->SetTransform(&oldMt);
} 

void GSprite::DrawFlipX(float x, float y, int alpha)
{
	D3DXMATRIX oldMt;
	spriteHandler->GetTransform(&oldMt);

	D3DXMATRIX newMt;
	D3DXVECTOR2 top_left = D3DXVECTOR2((float)x, (float)y);
	D3DXVECTOR2 rotate = D3DXVECTOR2(-1.0f, 1.0f);
	D3DXMatrixTransformation2D(&newMt, &top_left, 0.0f, &rotate, NULL, 0.0f, NULL);

	D3DXMATRIX finalMt = newMt * oldMt;

	spriteHandler->SetTransform(&finalMt);

	x -= _texture->FrameWidth;
	this->Draw(x, y, alpha);

	spriteHandler->SetTransform(&oldMt);
}

void GSprite::DrawFlipXIndex(int index, float x, float y, int alpha)
{
	RECT r = GetRectFrame(index);

	D3DXMATRIX oldMt;
	spriteHandler->GetTransform(&oldMt); 
	D3DXMATRIX newMt;  
	D3DXVECTOR2 top_left = D3DXVECTOR2(x, y); 
	D3DXVECTOR2 rotate = D3DXVECTOR2(-1.0f, 1.0f); 
	D3DXMatrixTransformation2D(&newMt, &top_left, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt; 
	spriteHandler->SetTransform(&finalMt);

	x -= _texture->FrameWidth;

	D3DXVECTOR3 p(x, y, 0);
	spriteHandler->Draw(_texture->Texture, &r, NULL, &p, D3DCOLOR_ARGB(alpha, 255, 255, 255));

	spriteHandler->SetTransform(&oldMt);
}
  
 
int GSprite::GetIndex()
{
	return _index;
}

 