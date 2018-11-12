#include "GSprite.h" 

GSprite::GSprite()
{
	_texture = NULL;
	_start = 0;
	_end = 0;
	_timeAni = 0;
	_index = 0;
	_timeLocal = 0;
	SetARGB();
}

GSprite::GSprite(const GSprite &sprite)
{
	_texture = sprite._texture;
	_start = sprite._start;
	_end = sprite._end;
	_timeAni = sprite._timeAni;
	_index = sprite._start;
	_timeLocal = sprite._timeLocal;
	SetARGB();
}

GSprite::GSprite(GTexture* texture, int start, int end, int timeAnimation)
: _texture(texture)
{
	_start = start;
	_end = end;
	_timeAni = timeAnimation;
	_index = start;
	_timeLocal = 0;
	SetARGB();
}

GSprite::GSprite(GTexture* texture, int timeAnimation)
: _texture(texture)
{
	_start = 0;
	_end = _texture->Count - 1;
	_timeAni = timeAnimation;
	_index = 0;
	_timeLocal = 0;
	SetARGB();
}

GSprite::~GSprite()
{
	/*if (_texture != NULL)
		delete _texture;*/
	// Không deleete texture vì đây là texture chung sẽ delete sau khi TextureManager bị delete
}

void GSprite::SetARGB(int r, int g, int b, int a)
{
	R = r;
	G = g;
	B = b;
	A = a;
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

void GSprite::SelectIndex(int index)
{
	_index = index;
}

void GSprite::Update(int ellapseTime)
{
	_timeLocal += ellapseTime;

	if (_timeLocal >= _timeAni)
	{
		_timeLocal = 0;
		this->Next();
	}
}

void GSprite::Draw(int X, int Y)
{
	LPD3DXSPRITE spriteHandler = Game::GetInstance()->GetSpriteHandler();
	RECT srect;
	srect.left = (_index % _texture->Cols)*_texture->FrameWidth;
	srect.top = (_index / _texture->Cols)*_texture->FrameHeight;
	srect.right = srect.left + _texture->FrameWidth;
	srect.bottom = srect.top + _texture->FrameHeight;

	D3DXVECTOR3 p((float)X, (float)Y, 0);
	spriteHandler->Draw(
		_texture->Texture,
		&srect,
		NULL,
		&p,
		D3DCOLOR_XRGB(R, G, B)
	);


}

void GSprite::DrawRandomColor(int X, int Y)
{
	LPD3DXSPRITE spriteHandler = Game::GetInstance()->GetSpriteHandler();
	RECT srect;
	srect.left = (_index % _texture->Cols)*_texture->FrameWidth;
	srect.top = (_index / _texture->Cols)*_texture->FrameHeight;
	srect.right = srect.left + _texture->FrameWidth;
	srect.bottom = srect.top + _texture->FrameHeight;

	int RR, GG, BB;

	switch (rand()%6)
	{
	case 0:
		RR = 255;
		GG = rand() % 256;
		BB = 0;
		break;

	case 1:
		RR = rand() % 256;
		GG = 255;
		BB = 0;
		break;

	case 2:
		RR = 0;
		GG = 255;
		BB = rand() % 256;
		break;

	case 3:
		RR = 0;
		GG = rand() % 256;
		BB = 255;
		break;

	case 4:
		RR = rand() % 256;
		GG = 0;
		BB = 255;
		break;

	case 5:
		RR = 255;
		GG = 0;
		BB = rand() % 256;
		break; 
	}

	D3DXVECTOR3 p((float)X, (float)Y, 0);
	spriteHandler->Draw(
		_texture->Texture,
		&srect,
		NULL,
		&p,
		D3DCOLOR_ARGB(255, RR,GG,BB)
	);
	 

}

void GSprite::DrawRandomColorFlipX(int x, int y)
{
	LPD3DXSPRITE spriteHandler = Game::GetInstance()->GetSpriteHandler();

	D3DXMATRIX oldMt;
	spriteHandler->GetTransform(&oldMt);

	D3DXMATRIX newMt;

	D3DXVECTOR2 top_left = D3DXVECTOR2((float)x, (float)y);

	D3DXVECTOR2 rotate = D3DXVECTOR2(-1.0f, 1.0f);

	D3DXMatrixTransformation2D(&newMt, &top_left, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;

	spriteHandler->SetTransform(&finalMt);

	x -= _texture->FrameWidth;
	this->DrawRandomColor(x, y);

	spriteHandler->SetTransform(&oldMt);
}











void GSprite::DrawRect(int X, int Y, RECT SrcRect)
{
	LPD3DXSPRITE spriteHandler = Game::GetInstance()->GetSpriteHandler();

	D3DXVECTOR3 position((float)X, (float)Y, 0.0f);
	spriteHandler->Draw(
		_texture->Texture,
		&SrcRect,
		NULL,
		&position,
		D3DCOLOR_XRGB(255, 255, 255)
	);
}

void GSprite::DrawFlipX(int x, int y)
{
	LPD3DXSPRITE spriteHandler = Game::GetInstance()->GetSpriteHandler();

	D3DXMATRIX oldMt;
	spriteHandler->GetTransform(&oldMt);

	D3DXMATRIX newMt;

	D3DXVECTOR2 top_left = D3DXVECTOR2((float)x, (float)y);

	D3DXVECTOR2 rotate = D3DXVECTOR2(-1.0f, 1.0f);

	D3DXMatrixTransformation2D(&newMt, &top_left, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;

	spriteHandler->SetTransform(&finalMt);

	x -= _texture->FrameWidth;
	this->Draw(x, y);

	spriteHandler->SetTransform(&oldMt);
}

void GSprite::DrawFlipXIndex(int index, int x, int y)
{
	RECT srect;

	LPD3DXSPRITE spriteHandler = Game::GetInstance()->GetSpriteHandler();

	srect.left = (index % _texture->Cols)*(_texture->FrameWidth);
	srect.top = (index / _texture->Cols)*(_texture->FrameHeight);
	srect.right = srect.left + _texture->FrameWidth;
	srect.bottom = srect.top + _texture->FrameHeight;




	D3DXMATRIX oldMt;
	spriteHandler->GetTransform(&oldMt); 
	D3DXMATRIX newMt;  
	D3DXVECTOR2 top_left = D3DXVECTOR2((float)x, (float)y); 
	D3DXVECTOR2 rotate = D3DXVECTOR2(-1.0f, 1.0f); 
	D3DXMatrixTransformation2D(&newMt, &top_left, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt; 
	spriteHandler->SetTransform(&finalMt);

	x -= _texture->FrameWidth;

	D3DXVECTOR3 p((float)x, (float)y, 0);
	spriteHandler->Draw(
		_texture->Texture,
		&srect,
		NULL,
		&p,
		D3DCOLOR_XRGB(R, G, B)
	);

	spriteHandler->SetTransform(&oldMt);

}
 
void GSprite::DrawIndex(int index, int X, int Y)
{
	RECT srect;

	LPD3DXSPRITE spriteHandler = Game::GetInstance()->GetSpriteHandler();

	srect.left = (index % _texture->Cols)*(_texture->FrameWidth);
	srect.top = (index / _texture->Cols)*(_texture->FrameHeight);
	srect.right = srect.left + _texture->FrameWidth;
	srect.bottom = srect.top + _texture->FrameHeight;
	D3DXVECTOR3 position(0, 0, 0);
	D3DXVECTOR3 center(0, 0, 0);
	position.x = (float)(X - _texture->FrameWidth / 2);
	position.y = (float)(Y - _texture->FrameHeight / 2);
	spriteHandler->Draw(
		_texture->Texture,
		&srect,
		&center,
		&position,
		D3DCOLOR_XRGB(A, R, G, B)  //color
		);
}
 
int GSprite::GetIndex()
{
	return _index;
}

 