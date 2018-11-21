#ifndef __DAGGER_H__
#define __DAGGER_H__

#include "Weapon.h"
#include "TextureManager.h"

#define DAGGER_SPEED 0.35f

class Dagger : 	public Weapon
{
public:
	Dagger();
	~Dagger();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);

	void Create(float simonX, float simonY, int simonDirection);
	 
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void RenderIcon(int X, int Y);


	bool isCollision(GameObject* obj);

	void Render(Camera *camera);



};

#endif