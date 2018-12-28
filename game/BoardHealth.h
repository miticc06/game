#ifndef __BOARDHEALTH_H__
#define __BOARDHEALTH_H__

#include "GSprite.h"
#include "GTexture.h"
#include "define.h"
#include "TextureManager.h"

#define BOARDHEALTH_MAX_CELL 16

#define BOARDHEALTH_FRAME_PLAYER 0
#define BOARDHEALTH_FRAME_NONE 1
#define BOARDHEALTH_FRAME_ENEMY 2

class BoardHealth
{
private:
	GSprite * _sprite;
	GTexture * _texture;
	float x, y;
public:
	BoardHealth(float X, float Y);

	~BoardHealth();
	void Draw(int HealthPlayer, int HealthEnemy);
};


#endif



