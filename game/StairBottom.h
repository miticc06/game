#pragma once
#include "GameObject.h"
class StairBottom :
	public GameObject
{
private:
	int width;
	int height;
 
public:
	StairBottom(float X, float Y, int Direction = 1);
	virtual ~StairBottom();


	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera);

};

