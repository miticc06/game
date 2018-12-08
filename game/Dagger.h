#ifndef __DAGGER_H__
#define __DAGGER_H__

#include "Weapon.h"
#include "TextureManager.h"
#include "Sound.h"
#define DAGGER_SPEED 0.35f

class Dagger : 	public Weapon
{
private:
	Camera * camera;

public:
	Dagger(Camera * camera);
	~Dagger();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);

	void Create(float simonX, float simonY, int simonDirection);
	 
 	void RenderIcon(int X, int Y);
	 
	void Render(Camera *camera);



};

#endif