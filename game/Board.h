#ifndef __BOARD_H__
#define __BOARD_H__

#include "GSprite.h"
#include "GTexture.h"
#include "Camera.h"
#include "define.h"
#include "Font.h"
#include "Simon.h"
#include "BoardHealth.h"
#include "TextureManager.h"
#include "Dagger.h"

#define BOARD_DEFAULT_POSITION_X 0.0f
#define BOARD_DEFAULT_POSITION_Y 0.0f

class Board
{
private:
	Font _font;
	BoardHealth * _boardHealth;
	
	GTexture *_texture;
	GSprite * _sprite;
	float x, y;

	string FillNumber(string s, UINT MaxNumber);
	 

	GSprite * _spriteIconDoubleShot;

 public:
	Board(float X, float Y);
	void Render(Simon * simon, int state, int RemainingTime, GameObject * boss);
	~Board();

	void SetTexture(GTexture * tex);
};





#endif 


