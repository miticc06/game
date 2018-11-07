#ifndef __TORCH_H__
#define __TORCH_H__

#include "GameObject.h"
class Torch : public GameObject
{

public:
	Torch(int X, int Y);
	~Torch();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera);

};

#endif