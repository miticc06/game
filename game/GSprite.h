#ifndef CSPRITE_H
#define CSPRITE_H
 

#include "GTexture.h"
 

class GSprite
{
private:
	LPD3DXSPRITE spriteHandler;



public:
	GTexture * _texture;

	int _start;
	int _end;
	int _index;
	DWORD _timeAni;
	DWORD _timeLocal;

	RECT GetRectFrame(int index);
	 
	GSprite(GTexture* texture, DWORD timeAnimation); 

 	void Next();

 	void Reset();
	void ResetTime();

 	void SelectIndex(int index);

 	void Update(DWORD dt);

 	void Draw(float X, float Y, int alpha = 255);

	void DrawRandomColor(float X, float Y, int alpha = 255);
	void DrawRandomColorFlipX(float x, float y, int alpha = 255);
	  
	void DrawFlipX(float x, float y, int alpha = 255);
	 
	void DrawFlipXIndex(int index, float x, float y, int alpha = 255);

 	 
	int GetIndex();
	 
	~GSprite();
 };

#endif