#include "GTexture.h"
  
int GTexture::GetFrameWidth()
{
	return frameWidth;
}

int GTexture::GetFrameHeight()
{
	return frameHeight;
}

int GTexture::GetColumn()
{
	return Column;
}

int GTexture::GetRow()
{
	return Row;
}

GTexture::GTexture(char* filePath, int column, int row, int totalframes, int R, int G, int B)
{
	Column = column;
	Row = row;
	TotalFrames = totalframes;
 	 
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFileA(filePath, &info);
	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n", filePath);
		return;
	}

	this->frameWidth = info.Width / Column;
	this->frameHeight = info.Height / Row;

	LPDIRECT3DDEVICE9 d3ddv = Game::GetInstance()->GetDirect3DDevice();
  
	result = D3DXCreateTextureFromFileExA(
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
		D3DCOLOR_XRGB(R, G, B),
		&info,
		NULL,
		&Texture);								// Created texture pointer
	  
	if (result != D3D_OK)
	{
		OutputDebugString(L"[ERROR] CreateTextureFromFile failed\n");
		return;
	}
}

GTexture::~GTexture()
{
	if (this->Texture != NULL)
		this->Texture->Release();
} 