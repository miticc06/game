#ifndef __SIMON_H__
#define __SIMON_H__


#define SIMON_POSITION_DEFAULT  50.0f, 0

#define SIMON_BBOX_WIDTH 60
#define SIMON_BBOX_HEIGHT 66

#define SIMON_BBOX_SITTING_HEIGHT 48



#define SIMON_GRAVITY 0.005f
#define SIMON_VJUMP 0.8f

#define SIMON_WALKING_SPEED 0.2f //0.12f 




#define SIMON_STATE_IDLE 0
#define SIMON_STATE_WALKING 1



#define SIMON_ANI_BEGIN_WALKING 1
#define SIMON_ANI_END_WALKING 3

#define SiMON_ANI_IDLE 0

#define SIMON_ANI_JUMPING 4

#define SIMON_ANI_SITTING 4




#include "GameObject.h"
#include "Weapon.h"
#include "MorningStar.h"

class Simon : public GameObject
{
public:
	
	bool isWalking;
	bool isJumping;
	bool isSitting;
	bool isAttacking;

	vector<Weapon*> _ListWeapon;

public:
	Simon();
	~Simon();



	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);


	virtual void Render(Camera * camera);
	 

	void Left();  // set lại hướng của simon
	void Right(); // set lại hướng của simon
	void Go();
	void Sit();
	void Jump();


	void Stop();

	void CollisionWithBrick(vector<LPGAMEOBJECT> *coObjects = NULL);

	void Attack(Weapon *w);


};






#endif