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
	GSprite(GTexture* Texture, DWORD TimeAnimation);
	virtual ~GSprite();

	GTexture * _texture;
	DWORD timeAccumulated;	 // thời gian chờ đã tích lũy
	DWORD timeAnimation; // thời gian phải chờ giữa các frame
	 
	RECT GetRectFrame(int index);
 	void Next();
	void ResetTime();

 	void SelectFrame(int index);

 	void Update(DWORD dt);

 	void Draw(float X, float Y, int alpha = 255, int R = 255, int G = 255, int B = 255);
	void DrawFlipX(float X, float Y, int alpha = 255, int R = 255, int G = 255, int B = 255);
	void DrawFlipXIndex(int idFrame, float X, float Y, int alpha = 255, int R = 255, int G = 255, int B = 255);
	  
	int GetCurrentFrame();
	int GetTotalFrames();
 };

#endif