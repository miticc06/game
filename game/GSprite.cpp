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
  
GSprite::GSprite(GTexture* Texture, DWORD TimeAnimation)
{
	_texture = Texture;
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
  
void GSprite::Draw(float X, float Y, int alpha, int R, int G, int B)
{
	RECT r = GetRectFrame(currentFrame);
	D3DXVECTOR3 p(trunc(X), trunc(Y), 0);
	spriteHandler->Draw(_texture->Texture, &r, NULL, &p, D3DCOLOR_ARGB(alpha, R, G, B));
}

void GSprite::DrawFlipX(float X, float Y, int alpha, int R, int G, int B)
{
	this->DrawFlipXIndex(currentFrame, X, Y, alpha, R, G, B);
}

void GSprite::DrawFlipXIndex(int idFrame, float X, float Y, int alpha, int R, int G, int B)
{
	RECT r = GetRectFrame(idFrame);

	D3DXMATRIX oldMt;
	spriteHandler->GetTransform(&oldMt); 
	D3DXMATRIX newMt;  
	D3DXVECTOR2 top_left = D3DXVECTOR2(X, X); 
	D3DXVECTOR2 rotate = D3DXVECTOR2(-1.0f, 1.0f); 
	D3DXMatrixTransformation2D(&newMt, &top_left, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt; 
	spriteHandler->SetTransform(&finalMt);

	X -= _texture->FrameWidth;

	D3DXVECTOR3 p(trunc(X), trunc(Y), 0);

	spriteHandler->Draw(_texture->Texture, &r, NULL, &p, D3DCOLOR_ARGB(alpha, R, G, B));

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

 