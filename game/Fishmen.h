#ifndef __FISHMEN_H__
#define __FISHMEN_H__
 
#include "GameObject.h" 
#include "Brick.h"
#include "Simon.h"
#include "FireBall.h"
#define FISHMEN_SPEED_Y_UP 0.4f
#define FISHMEN_SPEED_Y_DOWN 0.3f

#define FISHMEN_DY_JUMP 350 // nhảy lên khoảng 330px thì rớt xuống

#define FISHMEN_ANI_JUMP 2 // ani lúc nhảy
#define FISHMEN_ANI_WALK_BEGIN 1 // ani bắt đầu đi
#define FISHMEN_ANI_WALK_END 2 
#define FISHMEN_ANI_ATTACK 0 // ani lúc fishmen attack

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
	float xAccumulationAttack; // quãng đường đã đi tích lũy, để khi đi đủ giới hạn sẽ attack
	DWORD TimeAttack; // thời điểm attack
	 
	bool isRunning;
	FireBall * weapon;
	bool isAttacking;

	/* Lưu thành phần ngoài phục vụ xử lí */
	Simon* simon;
	vector<Weapon*> *listWeaponOfEnemy;
	Camera * camera;

public:
	Fishmen(float X, float Y, int Direction, Simon* simon, vector<Weapon*> *listWeaponOfEnemy, Camera * camera);
	virtual ~Fishmen();

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *listObject = NULL);
 	void Render(Camera * camera); 
	void Attack();
};

#endif 




