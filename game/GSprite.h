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

	GTexture * texture;

	DWORD timeAccumulated;	 // thời gian chờ đã tích lũy
	DWORD timeAnimation; // thời gian phải chờ giữa các frame
	 
	RECT GetRectFrame(int idFrame);
 	void Next();
	void ResetTime();

 	void SelectFrame(int idFrame);

 	void Update(DWORD dt);

 	void Draw(float X, float Y, int alpha = 255, int R = 255, int G = 255, int B = 255);
	void DrawFrame(int idFrame, float X, float Y, int alpha = 255, int R = 255, int G = 255, int B = 255);

	void DrawFlipX(float X, float Y, int alpha = 255, int R = 255, int G = 255, int B = 255);
	void DrawFrameFlipX(int idFrame, float X, float Y, int alpha = 255, int R = 255, int G = 255, int B = 255);
	  
	int GetCurrentFrame();
	int GetTotalFrames();
 };

#endif