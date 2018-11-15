#ifndef CSPRITE_H
#define CSPRITE_H
 

#include "GTexture.h"
 

class GSprite {
public:
	GTexture* _texture;

	int _start;
	int _end;
	int _index;
	int _timeAni;	//thời gian chuyển frame
	int _timeLocal;	

	GSprite();
	GSprite(const GSprite &sprite);
	GSprite(GTexture* texture, int timeAnimation);
	GSprite(GTexture* texture, int start, int end, int timeAnimation);

 	void Next();

 	void Reset();

 	void SelectIndex(int index);

 	void Update(int ellapseTime);

 	void Draw(int x, int y);

	void DrawRandomColor(int X, int Y);
	void DrawRandomColorFlipX(int x, int y);

	//Render with scale (-1, 1)
	void DrawFlipX(int x, int y);
	 
	void DrawFlipXIndex(int index, int x, int y);

	 
	void DrawRect(int X, int Y, RECT SrcRect);

	void DrawIndex(int index, int X, int Y);
	 
	int GetIndex();
	 
	~GSprite();

	int R, G, B, A;
	void SetARGB(int r = 255, int g = 255, int b = 255, int a = 255);
};

#endif