#include "Board.h"
 
string Board::FillNumber(string s, int MaxNumber)
{
	while (s.size() < MaxNumber)
		s = "0" + s;
	return s;
}

Board::Board(int X, int Y)
{
	_texture = new GTexture("Resources\\blackboard.png");
	_sprite = new GSprite(_texture, 0);
	x = X;
	y = Y;
}
 

void Board::Render(Camera * camera, Simon * simon , int state)
{ 
	_sprite->Draw(x,y);
	_font.Draw(x, y+15, "SCORE-");
	_font.Draw(x, y + 15, "SCORE-" + FillNumber(std::to_string(simon->GetScore()),6)  );

	_font.Draw(x, y+33, "PLAYER");
	_font.Draw(x, y+51, "ENEMY");


	_font.Draw(x+210, y + 15, "TIME");
	_font.Draw(x + 400 -20, y + 15, "STAGE");
	_font.Draw(x + 400+60, y + 15, std::to_string(state));


	_font.Draw(x + 400+15, y + 15+18, std::to_string(simon->GetHeartCollect())); // Số lượng tim nhặt dc
	_font.Draw(x + 400 + 15, y + 15 + 18+18, std::to_string(simon->GetLives())); // Số lượng tim nhặt dc


	_boardHealth.Draw(x + 100, y + 30, simon->GetHealth(), 5);

}


Board::~Board()
{
	SAFE_DELETE(_texture);
	SAFE_DELETE(_sprite);
}
