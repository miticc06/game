#ifndef CSPRITE_H
#define CSPRITE_H
 

#include "GTexture.h"
 

class GSprite {
public:
	GTexture* _texture;

	int _start;
	int _end;
	int _index;
	DWORD _timeAni;	//thời gian chuyển frame
	DWORD _timeLocal;

	GSprite();
	GSprite(const GSprite &sprite);
	GSprite(GTexture* texture, DWORD timeAnimation);
	GSprite(GTexture* texture, int start, int end, DWORD timeAnimation);

 	void Next();

 	void Reset();
	void ResetTime();

 	void SelectIndex(int index);

 	void Update(DWORD dt);

 	void Draw(int x, int y, int alpha = 255);
	void Draw(float X, float Y, int alpha = 255);

	void DrawRandomColor(int X, int Y, int alpha = 255);
	void DrawRandomColorFlipX(int x, int y, int alpha = 255);
	 

	//Render with scale (-1, 1)
	void DrawFlipX(int x, int y, int alpha = 255);
	 
	void DrawFlipXIndex(int index, int x, int y, int alpha = 255);

	 
	void DrawRect(int X, int Y, RECT SrcRect, int alpha = 255);

	void DrawIndex(int index, int X, int Y, int alpha = 255);
	 
	int GetIndex();
	 
	~GSprite();

	int R, G, B, A;
	void SetARGB(int r = 255, int g = 255, int b = 255, int a = 255);
};

#endif