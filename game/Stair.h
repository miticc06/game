#ifndef __STAIR_H__
#define __STAIR_H__

#include "GameObject.h"
class Stair : public GameObject
{
private:
	int width;
	int height;
	int t; // kiểu object cầu thang, 1 ở dưới, 2 ở trên

public:
	Stair(int X, int Y, int W, int H, int T, int Trend = 1);
	virtual ~Stair();


	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera);

}; 

#endif


