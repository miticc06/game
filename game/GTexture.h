#ifndef __CTEXTURE_H__
#define __CTEXTURE_H__
 
#include "Game.h"
#include "define.h"

class GTexture 
{
public:
	LPDIRECT3DTEXTURE9 Texture;
	char* FileName;  
	RECT Size;
	int Cols;
	int Rows;	
	int Count;	
	int FrameWidth;	
	int FrameHeight;

	GTexture(char* _fileName, int cols = 1, int rows = 1, int count = 1, int R = 255, int G = 0, int B = 255);
 	~GTexture();
	void Draw(int x, int y);

protected: 
	void Load(int R, int G, int B);
};

#endif