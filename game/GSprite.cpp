#include "GSprite.h" 

RECT GSprite::GetRectFrame(int index)
{
	RECT res; 
	res.left = (index % _texture->NumColumn)*(_texture->FrameWidth);
	res.top = (index / _texture->NumColumn)*(_texture->FrameHeight);
	res.right = res.left + _texture->FrameWidth;
	res.bottom = res.top + _texture->FrameHeight;
	return res;
}
  
GSprite::GSprite(GTexture* texture, DWORD TimeAnimation)
{
	_texture = texture;
	currentFrame = 0;
 	totalFrames = _texture->TotalFrames - 1;
	this->timeAnimation = TimeAnimation;

	spriteHandler = Game::GetInstance()->GetSpriteHandler();
}

GSprite::~GSprite()
{ 
}
 
void GSprite::Next()
{
	currentFrame++;
	if (currentFrame > totalFrames)
		currentFrame = 0;
}
 
void GSprite::ResetTime()
{ 
	timeAccumulated = 0; 
}

void GSprite::SelectFrame(int index)
{
	currentFrame = index;
	//timeAccumulated = 0;
}

void GSprite::Update(DWORD dt)
{
	timeAccumulated += dt;
	if (timeAccumulated >= timeAnimation)
	{
		timeAccumulated -= timeAnimation;
		this->Next();
	}
}
  
void GSprite::Draw(float X, float Y, int alpha)
{ 
	RECT r = GetRectFrame(currentFrame);
	D3DXVECTOR3 p(trunc(X), trunc(Y), 0);
	spriteHandler->Draw(_texture->Texture, &r, NULL, &p, D3DCOLOR_ARGB(alpha, 255, 255, 255));
} 

void GSprite::DrawRandomColor(float X, float Y, int alpha)
{
	RECT r = GetRectFrame(currentFrame);
	 
 
	D3DXVECTOR3 p(trunc(X), trunc(Y), 0);

	spriteHandler->Draw(_texture->Texture, &r, NULL, &p, D3DCOLOR_ARGB(alpha, rand() % 256, rand() % 256, rand() % 256));
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

void GSprite::DrawFlipXIndex(int index, float X, float Y, int alpha)
{
	RECT r = GetRectFrame(index);

	D3DXMATRIX oldMt;
	spriteHandler->GetTransform(&oldMt); 
	D3DXMATRIX newMt;  
	D3DXVECTOR2 top_left = D3DXVECTOR2(X, X); 
	D3DXVECTOR2 rotate = D3DXVECTOR2(-1.0f, 1.0f); 
	D3DXMatrixTransformation2D(&newMt, &top_left, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt; 
	spriteHandler->SetTransform(&finalMt);

	Y -= _texture->FrameWidth;

	D3DXVECTOR3 p(trunc(X), trunc(Y), 0);

	spriteHandler->Draw(_texture->Texture, &r, NULL, &p, D3DCOLOR_ARGB(alpha, 255, 255, 255));

	spriteHandler->SetTransform(&oldMt);
}
  
 
int GSprite::GetCurrentFrame()
{
	return currentFrame;
}

int GSprite::GetTotalFrames()
{
	return totalFrames;
}

 