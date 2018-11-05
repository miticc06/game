#ifndef __SIMON_H__
#define __SIMON_H__


#define SIMON_BBOX_WIDTH 60
#define SIMON_BBOX_HEIGHT 64
#define SIMON_BBOX_SITTING_HEIGHT 48



#define SIMON_GRAVITY 0.01f

#define SIMON_WALKING_SPEED 0.15f 




#define SIMON_STATE_IDLE 0
#define SIMON_STATE_WALKING 1



#define SIMON_ANI_BEGIN_WALKING 1
#define SIMON_ANI_END_WALKING 3

#define SiMON_ANI_IDLE 0

#define SIMON_ANI_SITTING 4




#include "GameObject.h"
class Simon : public GameObject
{
protected:
	
	bool isWalking;
	bool isJumping;
	bool isSitting;


public:
	Simon();
	~Simon();



	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);


	virtual void Render();

	void SetState(int state);


	void Left();  // set lại hướng của simon
	void Right(); // set lại hướng của simon
	void Go();
	void Sit();



	void Stop();

};






#endif