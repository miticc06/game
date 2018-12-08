#ifndef  __THROWINGAXE_H__
#define __THROWINGAXE_H__
  
#define THROWINGAXE_SPEED_X 0.2f
#define THROWINGAXE_SPEED_Y 0.55f
#define THROWINGAXE_GRAVITY 0.0015f


#include "Weapon.h"
#include "Sound.h"
class ThrowingAxe :
	public Weapon
{
private:
	GSprite * _spriteIcon;
	Camera * camera;

public:

	ThrowingAxe(Camera * camera);
	virtual ~ThrowingAxe();
	 
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Create(float simonX, float simonY, int simonDirection);
	virtual void RenderIcon(int X, int Y);

};

#endif
