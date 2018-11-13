#ifndef __BRICK_H__
#define __BRICK_H__


#include "GameObject.h" 
#include "TextureManager.h"

class Brick : public GameObject
{
protected:
	int width;
	int height;
	int model;

public:
	Brick(int X, int Y, int W, int H, int Model);
	virtual void Render(Camera * camera);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};


#endif