#ifndef __BOARD_H__
#define __BOARD_H__

#include "GSprite.h"
#include "GTexture.h"
#include "Camera.h"
#include "define.h"
#include "Font.h"
class Board
{
private:
	Font _font;

	GTexture *_texture;
	GSprite * _sprite;
	int x, y;

	string information;

public:
	Board(int X, int Y);
	void Render(Camera *camera);
	~Board();
};





#endif 


