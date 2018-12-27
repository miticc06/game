#ifndef __FIREBALL_H__
#define __FIREBALL_H__


#include "Weapon.h" 
#define FIREBALL_SPEED 0.21f

class FireBall :
	public Weapon
{
public:
	FireBall();
	virtual ~FireBall();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Create(float X, float Y, int Direction);
 	void RenderIcon(int X, int Y); 

	void Render(Camera *camera);

};




#endif