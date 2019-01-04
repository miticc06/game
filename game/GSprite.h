#ifndef __GSPRITE_H__
#define __GSPRITE_H__
 
#include "GTexture.h"
 
class GSprite
{
private:
	LPD3DXSPRITE spriteHandler;
	int currentFrame;
	int totalFrames;

public:
	GSprite(GTexture* texture, DWORD TimeAnimation);
	~GSprite();

	GTexture * _texture;
	DWORD timeAccumulated;	 // thời gian chờ đã tích lũy
	DWORD timeAnimation; // thời gian phải chờ giữa các frame
	 
	RECT GetRectFrame(int index);
 	void Next();
	void ResetTime();

 	void SelectFrame(int index);

 	void Update(DWORD dt);

 	void Draw(float X, float Y, int alpha = 255);
	void DrawFlipX(float x, float y, int alpha = 255);
	void DrawFlipXIndex(int index, float x, float y, int alpha = 255);

	void DrawRandomColor(float X, float Y, int alpha = 255);
	void DrawRandomColorFlipX(float x, float y, int alpha = 255);
	  
	int GetCurrentFrame();
	int GetTotalFrames();
 };

#endif