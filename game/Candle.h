#ifndef __Candle_H__
#define __Candle_H__


#include "GameObject.h"
class Candle : 	public GameObject
{
public:
	Candle(int X, int Y);
	~Candle();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera);
};


#endif

