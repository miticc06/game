#include "GSprite.h" 

RECT GSprite::GetRectFrame(int idFrame)
{
	RECT res; 
	res.left = (idFrame % texture->GetColumn())* texture->GetFrameWidth();
	res.top = (idFrame / texture->GetColumn())* texture->GetFrameHeight();
	res.right = res.left + texture->GetFrameWidth();
	res.bottom = res.top + texture->GetFrameHeight();
	return res;
}
  
GSprite::GSprite(GTexture* Texture, DWORD TimeAnimation)
{
	texture = Texture;
	currentFrame = 0;
 	totalFrames = texture->TotalFrames - 1;
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

void GSprite::SelectFrame(int idFrame)
{
	currentFrame = idFrame;
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
	DrawFrame(currentFrame, X, Y, alpha, R, G, B);
}

void GSprite::DrawFrame(int idFrame, float X, float Y, int alpha, int R, int G, int B)
{
	RECT r = GetRectFrame(idFrame);
	D3DXVECTOR3 p(trunc(X), trunc(Y), 0);
	spriteHandler->Draw(texture->Texture, &r, NULL, &p, D3DCOLOR_ARGB(alpha, R, G, B));
}

void GSprite::DrawFlipX(float X, float Y, int alpha, int R, int G, int B)
{
	this->DrawFrameFlipX(currentFrame, X, Y, alpha, R, G, B);
}

void GSprite::DrawFrameFlipX(int idFrame, float X, float Y, int alpha, int R, int G, int B)
{
	RECT r = GetRectFrame(idFrame);

	D3DXMATRIX AA, BB;
	spriteHandler->GetTransform(&AA); 
	D3DXMatrixTransformation2D(&BB, &D3DXVECTOR2(X, X), 0.0f, &D3DXVECTOR2(-1.0f, 1.0f), NULL, 0.0f, NULL);
	D3DXMATRIX CC = AA * BB;
	spriteHandler->SetTransform(&CC);
	X -= texture->GetFrameWidth();
	D3DXVECTOR3 p(trunc(X), trunc(Y), 0);
	spriteHandler->Draw(texture->Texture, &r, NULL, &p, D3DCOLOR_ARGB(alpha, R, G, B));
	spriteHandler->SetTransform(&AA); // Reset ve ban dau
}
  
 
int GSprite::GetCurrentFrame()
{
	return currentFrame;
}

int GSprite::GetTotalFrames()
{
	return totalFrames;
}

 