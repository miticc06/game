#pragma once
#include "GameObject.h"
class ObjectHidden : public GameObject
{
private:
	int width;
	int height;

public:
	ObjectHidden(int X, int Y, int W, int H);
	~ObjectHidden();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera);

};

