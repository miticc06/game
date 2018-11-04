#ifndef __SPRITE_H__
#define __SPRITE_H__


#include <Windows.h>
#include <d3dx9.h> 
#include "define.h"

#include "Game.h"
#include "debug.h"
#include <string>
#include <fstream>
#include <iostream> 

using namespace std;

class Sprite
{
protected: 
	LPDIRECT3DTEXTURE9 _texture;

public:
	Sprite();
	~Sprite();

	Sprite(LPWSTR filePath, D3DCOLOR transparentColor);
	void Draw(float x, float y, RECT r, int alpha = 255);
	LPDIRECT3DTEXTURE9 GetTexture();

};





#endif