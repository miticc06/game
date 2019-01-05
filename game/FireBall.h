#ifndef __FIREBALL_H__
#define __FIREBALL_H__


#include "Weapon.h" 
#define FIREBALL_SPEED 0.21f

class FireBall :
	public Weapon
{
private :
	Camera *camera;

public:
	FireBall(Camera *camera);
	virtual ~FireBall();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Attack(float X, float Y, int Direction);
 	void RenderIcon(float X, float Y); 

	void Render(Camera *camera);

};




#endif