#ifndef __BOARD_H__
#define __BOARD_H__

#include "GSprite.h"
#include "GTexture.h"
#include "Camera.h"

class Board
{
private:
	GTexture *_texture;
	GSprite * _sprite;
	int x, y;

public:
	Board(int X, int Y);
	void Render(Camera *camera);
	~Board();
};





#endif 


