#ifndef __TORCH_H__
#define __TORCH_H__

#include "GameObject.h"
#include "TextureManager.h"

class Torch : public GameObject
{

public:
	Torch(int X = 0, int Y = 0);
	~Torch();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera);

};

#endif