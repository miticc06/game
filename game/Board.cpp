#include "Board.h"



Board::Board(int X, int Y)
{
	_texture = new GTexture("Resources\\blackboard.png");
	_sprite = new GSprite(_texture, 0);
	x = X;
	y = Y;
}

void Board::Render(Camera * camera)
{
	_sprite->Draw(x, y);
}


Board::~Board()
{
	SAFE_DELETE(_texture);
	SAFE_DELETE(_sprite);
}
