#ifndef __BRICK_H__
#define __BRICK_H__


#include "GameObject.h" 
#include "TextureManager.h"

#define BRICK_MODEL_1 1 // gạch màn 1, 32px
#define BRICK_MODEL_2 2 // gạch màn 2,32px
#define BRICK_MODEL_3 3 // gạch loại 3, ô nhỏ 16px
#define BRICK_MODEL_TRANSPARENT 4 // gạch trong suốt
#define BRICK_MODEL_3_3_32 5 // gạch loại 3, 3 ô nhỏ - 32px 
#define BRICK_MODEL_3_4_32 6 // gạch loại 3, đủ 4 ô nhỏ - 32px 

class Brick : public GameObject
{
protected:
	int width;
	int height;
	int model;

public:
	Brick(float X, float Y, int W, int H, int Model);
	virtual void Render(Camera * camera);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	int GetModel();
};


#endif