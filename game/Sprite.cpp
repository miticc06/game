#include "Sprite.h"



Sprite::Sprite()
{
}


Sprite::~Sprite()
{
}



void Sprite::Draw(float x, float y, RECT r, int alpha)
{
	Game * game = Game::GetInstance();
	game->Draw(x, y, _texture, r, alpha);
}

LPDIRECT3DTEXTURE9 Sprite::GetTexture()
{
	return _texture;
}



Sprite::Sprite(LPWSTR filePath, D3DCOLOR transparentColor)
{
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(filePath, &info);
	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n", filePath);
		return;
	}

	LPDIRECT3DDEVICE9 d3ddv = Game::GetInstance()->GetDirect3DDevice();


	result = D3DXCreateTextureFromFileEx(
		d3ddv,								// Pointer to Direct3D device object
		filePath,							// Path to the image to load
		info.Width,							// Texture width
		info.Height,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transparentColor,
		&info,
		NULL,
		&_texture);								// Created texture pointer

	if (result != D3D_OK)
	{
		OutputDebugString(L"[ERROR] CreateTextureFromFile failed\n");
		return;
	}
	DebugOut(L"[INFO] Texture loaded Ok: %s \n", filePath);
}