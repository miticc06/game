#include "GTexture.h"

GTexture::GTexture(char* _fileName, int cols, int rows, int count, int Showbox)
{
	Cols = cols;
	Rows = rows;
	Count = count;
	FileName = _fileName;
	this->Load(Showbox);
}

GTexture::GTexture(char* _fileName, int cols, int rows, int count, int R, int G, int B)
{
	Cols = cols;
	Rows = rows;
	Count = count;
	FileName = _fileName;
	this->Load(R, G, B);
}

GTexture::~GTexture()
{
	if(this->Texture != NULL)
		this->Texture->Release();
}

void GTexture::Draw(int x, int y) 
{
	LPD3DXSPRITE spriteHandler = Game::GetInstance()->GetSpriteHandler();

	D3DXVECTOR3 position((float)x, (float)y, 0);
	spriteHandler->Draw( Texture, &Size, NULL, &position, 0xFFFFFFFF );
}

void GTexture::Load(int ShowBox)
{
	D3DXIMAGE_INFO info;
	HRESULT result;

	LPDIRECT3DDEVICE9 G_Device = Game::GetInstance()->GetDirect3DDevice();


	result = D3DXGetImageInfoFromFileA(FileName, &info);

	RECT s = { 0, 0, info.Width, info.Height };
	this->Size = s;

	FrameWidth = info.Width / Cols;
	FrameHeight = info.Height / Rows;

	if (result != D3D_OK)
	{
	//	GLMessage("Can not load texture");
	//	GLTrace("[texture.h] Failed to get information from image file [%s]", FileName);
		OutputDebugStringA(FileName);
		return;
	}

	result = D3DXCreateTextureFromFileExA(
		G_Device,
		FileName,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, ShowBox, 255), //color
		&info,
		0,
		&Texture
	);
	
	if (result != D3D_OK)
	{
		//GLMessage("Can not load texture");
	//	GLTrace("[texture.h] Failed to create texture from file '%s'", FileName);
		return;
	}
}

void GTexture::Load(int R, int G, int B)
{
	D3DXIMAGE_INFO info;
	HRESULT result;

	LPDIRECT3DDEVICE9 G_Device = Game::GetInstance()->GetDirect3DDevice();



	result = D3DXGetImageInfoFromFileA(FileName, &info);

	RECT s = { 0, 0, info.Width, info.Height };
	this->Size = s;

	FrameWidth = info.Width / Cols;
	FrameHeight = info.Height / Rows;

	if (result != D3D_OK)
	{
		//GLMessage("Can not load texture");
		//GLTrace("[texture.h] Failed to get information from image file [%s]", FileName);
		OutputDebugStringA(FileName);
		return;
	}

	result = D3DXCreateTextureFromFileExA(
		G_Device,
		FileName,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(R, G, B), //color
		&info,
		0,
		&Texture
	);

	if (result != D3D_OK)
	{
		//GLMessage("Can not load texture");
		//GLTrace("[texture.h] Failed to create texture from file '%s'", FileName);
		return;
	}
}