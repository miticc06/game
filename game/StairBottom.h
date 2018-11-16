#pragma once
#include "GameObject.h"
class StairBottom :
	public GameObject
{
private:
	int width;
	int height;
 
public:
	StairBottom(int X, int Y, int Trend = 1);
	virtual ~StairBottom();


	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera);

};

