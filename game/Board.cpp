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
	_sprite->Draw(x,y);
	_font.Draw((float)x, (float)y+15, "SCORE-");
	_font.Draw((float)x, (float)y+33, "PLAYER");
	_font.Draw((float)x, (float)y+51, "ENEMY");


	_font.Draw((float)x+210, (float)y + 15, "TIME");
	_font.Draw((float)x + 400, (float)y + 15, "STAGE");

}


Board::~Board()
{
	SAFE_DELETE(_texture);
	SAFE_DELETE(_sprite);
}
