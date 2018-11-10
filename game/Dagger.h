#ifndef __DAGGER_H__
#define __DAGGER_H__

#include "Weapon.h"

#define DAGGER_SPEED 0.35f

class Dagger : 	public Weapon
{
public:
	Dagger();
	~Dagger();

	void Update(DWORD dt, vector<LPOBJECT> *coObjects = NULL);

	void Create(float simonX, float simonY, int simonTrend);
	 
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	bool isCollision(Object* obj);

	void Render(Camera *camera);



};

#endif