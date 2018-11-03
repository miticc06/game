#include "Texture.h"



Texture::Texture()
{
	_color = COLOR_BLACK;
	_texture = nullptr;
}


Texture::~Texture()
{
}

HRESULT Texture::loadFromFile(LPD3DXSPRITE spriteHandle, LPWSTR filePath, D3DXCOLOR color, D3DXCOLOR colorkey)
{
	HRESULT result;

	result = D3DXGetImageInfoFromFile(filePath, &this->_imageInfo);
	if (result != D3D_OK)
	{
		return result;
	}

	LPDIRECT3DDEVICE9 _device = Game::GetInstance()->GetDirect3DDevice();
	spriteHandle->GetDevice(&_device);

	result = D3DXCreateTextureFromFileEx(
		_device,
		filePath,
		this->_imageInfo.Width,
		this->_imageInfo.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		colorkey,
		&this->_imageInfo,
		nullptr,
		&this->_texture);

	_color = color;

	return result;
}
 

void Texture::Draw(LPD3DXSPRITE spriteHandle, float x, float y)
{
	D3DXVECTOR3 position((float)x, (float)y, 0);

	RECT s = { 0, 0, _imageInfo.Width, _imageInfo.Height };

	spriteHandle->Draw(_texture,  &s , NULL, &position, 0xFFFFFFFF);
}

void Texture::setColor(D3DXCOLOR color)
{
	_color = color;
}

D3DXCOLOR Texture::getColor()
{
	return _color;
}

int Texture::getWidth()
{
	return _imageInfo.Width;
}

int Texture::getHeight()
{
	return _imageInfo.Height;
}

void Texture::release()
{
	_texture->Release();
}
