#ifndef __FONT_H__
#define __FONT_H__

#include "GSprite.h"
#include "GTexture.h"
#include "define.h"


class Font
{
private:
	GSprite * _sprite;
	GTexture * _texture;

public:
	Font();
	~Font();
	void Draw(float x, float y, string s);
};





#endif 



