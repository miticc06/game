#ifndef __STOPWATCH_H__
#define __STOPWATCH_H__

#include "Weapon.h"
class StopWatch :
	public Weapon
{
private:
	DWORD TimeSpent;
	
public:
	StopWatch();
	virtual ~StopWatch();

	virtual void Create(float simonX, float simonY, int simonDirection);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera *camera);
 	virtual bool isCollision(GameObject* obj); 
	virtual void RenderIcon(int X, int Y);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

};

#endif