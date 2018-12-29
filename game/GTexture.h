#ifndef __CTEXTURE_H__
#define __CTEXTURE_H__
 
#include "Game.h"
#include "define.h"

class GTexture 
{
private:
	RECT Size;
	 
public:
 	int NumColumn, NumRow, TotalFrames, FrameWidth, FrameHeight;

	LPDIRECT3DTEXTURE9 Texture;

	GTexture(char* filePath, int column = 1, int row = 1, int totalframes = 1, int R = 255, int G = 0, int B = 255);
 	~GTexture(); 
};

#endif