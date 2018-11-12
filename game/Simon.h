#ifndef __SIMON_H__
#define __SIMON_H__


#define SIMON_POSITION_DEFAULT  50.0f, 0

#define SIMON_BBOX_WIDTH 60
#define SIMON_BBOX_HEIGHT 66

#define SIMON_BBOX_SITTING_HEIGHT 48



#define SIMON_GRAVITY 0.005f//0.005f
#define SIMON_VJUMP 0.9f

#define SIMON_WALKING_SPEED 0.12f //0.12f 




#define SIMON_STATE_IDLE 0
#define SIMON_STATE_WALKING 1



#define SIMON_ANI_WALKING_BEGIN 1
#define SIMON_ANI_WALKING_END 3

#define SiMON_ANI_IDLE 0

#define SIMON_ANI_JUMPING 4

#define SIMON_ANI_SITTING 4

#define SIMON_ANI_SITTING_ATTACKING_BEGIN 15
#define SIMON_ANI_SITTING_ATTACKING_END 17

#define SIMON_ANI_STANDING_ATTACKING_BEGIN 5
#define SIMON_ANI_STANDING_ATTACKING_END 7

#define TIME_FREEZE_MAX 500

#include "GameObject.h"
#include "Weapon.h"
#include "MorningStar.h"

class Simon : public GameObject
{
private:
	int HeartCollect; // số lượng item heart người chơi nhặt được
	int Lives;
	int score;


	bool isFreeze; // Trạng thái đóng băng thay đổi màu liên tục
	DWORD TimeFreeze; // thời gian đã đóng băng


public:
	bool isWalking;
	bool isJumping;
	bool isSitting;
	bool isAttacking;


public:
	Simon();
	~Simon();

	Weapon* _weaponMain;
	Weapon* _weaponSub;


	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera);
	 
//	void RenderSimon(Camera * camera)

	void Left();  // set lại hướng của simon
	void Right(); // set lại hướng của simon
	void Go();
	void Sit();
	void Jump();
	void Stop();


	void SetHeartCollect(int h);
	int GetHeartCollect();

	void CollisionWithBrick(vector<LPOBJECT> *coObjects = NULL);
 
	void Attack(Weapon *w);

	int GetLives();
	void SetLives(int l);
	int GetScore();
	void SetScore(int s);

	bool GetFreeze();
	void SetFreeze(int f);
	void UpdateFreeze(DWORD dt);



	bool isCollisionWithItem(Item * objItem);


};






#endif