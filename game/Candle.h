#ifndef __Candle_H__
#define __Candle_H__


#include "GameObject.h"
class Candle : 	public GameObject
{
public:
	Candle(float X, float Y);
	~Candle();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera);
};


#endif

