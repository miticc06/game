#include "GTexture.h"
  
GTexture::GTexture(char* filePath, int cols, int rows, int count, int R, int G, int B)
{
	Cols = cols;
	Rows = rows;
	Count = count;
 	 
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFileA(filePath, &info);
	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n", filePath);
		return;
	}

	FrameWidth = info.Width / Cols;
	FrameHeight = info.Height / Rows;

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
	if(this->Texture != NULL)
		this->Texture->Release();
}
//
//void GTexture::Draw(int x, int y) 
//{
//	LPD3DXSPRITE spriteHandler = Game::GetInstance()->GetSpriteHandler();
//	D3DXVECTOR3 position((float)x, (float)y, 0);
//	spriteHandler->Draw( Texture, &Size, NULL, &position, 0xFFFFFFFF);
//}
//   