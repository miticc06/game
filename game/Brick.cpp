#include "Brick.h"
 

Brick::Brick(int X, int Y, int W, int H)
{
	type = eID::BRICK;
	_texture = new GTexture("Resources\\ground\\2.png", 1, 1, 1, 0);
	_sprite = new GSprite(_texture, 1000);
	this->x = X;
	this->y = Y;
	this->width = W;
	this->height = H;
}

void Brick::Render()
{
	for (int i = 0; i < (int)ceil(width / BRICK_FRAME_WIDTH); i++)
		for (int j = 0; j < (int)ceil(height / BRICK_FRAME_HEIGHT); j++)
			_sprite->Draw(x + i * BRICK_FRAME_WIDTH, y + j * BRICK_FRAME_HEIGHT);

}

void Brick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + (float)ceil(width / BRICK_FRAME_WIDTH)*BRICK_FRAME_WIDTH;
	b = y + (float)ceil(height / BRICK_FRAME_HEIGHT)*BRICK_FRAME_HEIGHT;
}