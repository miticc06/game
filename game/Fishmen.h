﻿#ifndef __FISHMEN_H__
#define __FISHMEN_H__
 
#include "GameObject.h" 
#include "Brick.h"
#include "Simon.h"
#include "FireBall.h"
#define FISHMEN_SPEED_Y_UP 0.4f
#define FISHMEN_SPEED_Y_DOWN 0.3f

#define FISHMEN_DY_JUMP 350 // nhảy lên khoảng 330px thì rớt xuống

#define FISHMEN_ANI_JUMP 2 // nhảy lên khoảng 330px thì rớt xuống

#define FISHMEN_GRAVITY 0.01f
#define FISHMEN_SPEED_X 0.07f

#define FISHMEN_DX_LIMIT 140 // đi được khoảng 140px thì đổi hướng
#define FISHMEN_DX_ATTACK_LIMIT 130 // đi được khoảng 140px thì đổi hướng

#define FISHMEN_TIME_LIMIT_WAIT_AFTER_ATTACK 700 // thời gian fishmen phải đứng lại chờ trước khi đi tiếp, sau khi attack

class Fishmen : public GameObject
{
private:
	float yInit; // vị trí y lúc khởi tạo
	float xInit; 
 
	float xBefore;
	float xAfter;
	float xAccumulationAttack;
	DWORD TimeAttack; // thời điểm attack
	 
	bool isRunning;
	FireBall * weapon;
	bool isAttacking;
public:
	Fishmen(float X = 0, float Y = 0, int Direction = -1);
	virtual ~Fishmen();

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *listObject = NULL);
	void UpdateCustom(DWORD dt, vector<LPGAMEOBJECT> *listObject, Simon* simon, vector<Weapon*> *listWeaponOfEnemy);
	void Render(Camera * camera);

	void Attack(vector<Weapon*> *listWeaponOfEnemy);
};

#endif 




