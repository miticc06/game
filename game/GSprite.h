#ifndef CSPRITE_H
#define CSPRITE_H
 

#include "GTexture.h"
 

class GSprite
{
private:
	LPD3DXSPRITE spriteHandler;
	int currentFrame;
	int totalFrames;



public:
	GTexture * _texture;
	DWORD timeAccumulated;	 // thời gian chờ đã tích lũy
	DWORD timeAnimation; // thời gian phải chờ giữa các frame



	GSprite(GTexture* texture, DWORD TimeAnimation); 
	~GSprite();


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