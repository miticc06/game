#ifndef __SIMON_H__
#define __SIMON_H__


#include "GameObject.h"
#include "Weapon.h"
#include "MorningStar.h"
#include "Sound.h"
#include "ThrowingAxe.h"
#include "Dagger.h"
#include "HolyWater.h"
#include "StopWatch.h"
#include "Boomerang.h"

#define SIMON_POSITION_DEFAULT  50.0f, 300.0f

#define SIMON_BBOX_WIDTH 60
#define SIMON_BBOX_HEIGHT 63
#define SIMON_BBOX_SITTING_HEIGHT 45
#define SIMON_BBOX_JUMPING_HEIGHT 45

#define PULL_UP_SIMON_AFTER_SITTING 18.0f // Kéo simon lên 18px sau khi ngồi rồi đứng dậy, tránh overlaping do BBOX bottom thu lại khi ngồi

 
#define SIMON_GRAVITY 0.005f 
#define SIMON_GRAVITY_JUMPING 0.001f 
#define SIMON_GRAVITY_HURTING 0.001f


#define SIMON_VJUMP 0.34f
#define SIMON_VJUMP_HURTING 0.2f // nhảy lúc bị đau
#define PULL_UP_SIMON_AFTER_JUMPING 18.0f // Kéo simon lên 18px sau khi nhảy, tránh overlaping do BBOX bottom thu lại khi nhảy


#define SIMON_WALKING_SPEED 0.12f //0.12f 

#define SIMON_STATE_IDLE 0
#define SIMON_STATE_WALKING 1

#define SIMON_ANI_WALKING_BEGIN 1
#define SIMON_ANI_WALKING_END 3

#define SIMON_ANI_IDLE 0

#define SIMON_ANI_JUMPING 4

#define SIMON_ANI_SITTING 4



/*Ani đang ngồi đánh*/
#define SIMON_ANI_SITTING_ATTACKING_BEGIN 15
#define SIMON_ANI_SITTING_ATTACKING_END 17

/*Ani đang đứng đánh*/
#define SIMON_ANI_STANDING_ATTACKING_BEGIN 5
#define SIMON_ANI_STANDING_ATTACKING_END 7

/*Ani đang đi lên cầu thang đánh*/
#define SIMON_ANI_STAIR_UP_ATTACKING_BEGIN 21
#define SIMON_ANI_STAIR_UP_ATTACKING_END 23

/*Ani đang đi xuống cầu thang đánh*/
#define SIMON_ANI_STAIR_DOWN_ATTACKING_BEGIN 18
#define SIMON_ANI_STAIR_DOWN_ATTACKING_END 20

/* Time Ani attack */ 
#define SIMON_TIME_WAIT_ANI_ATTACKING 120// thời gian thời của mỗi frame khi tấn công


#define SIMON_ANI_STAIR_GO_UP_BEGIN 12
#define SIMON_ANI_STAIR_GO_UP_END 13

#define SIMON_ANI_STAIR_GO_DOWN_BEGIN 10
#define SIMON_ANI_STAIR_GO_DOWN_END 11



#define SIMON_ANI_HURTING 8

#define SIMON_ANI_HIDE_FACE 9


#define SIMON_SPEED_ONSTAIR 0.09f 



#define SIMON_ANI_STAIR_STANDING_UP 12
#define SIMON_ANI_STAIR_STANDING_DOWN 10


#define TIME_FREEZE_MAX 500


#define SIMON_DEFAULT_HEALTH 16
#define SIMON_DEFAULT_HEARTCOLLECT 5
#define SIMON_DEFAULT_SCORE 0
#define SIMON_DEFAULT_LIVES 3

#define SIMON_UNTOUCHABLE_TIME 2000 


class Simon : public GameObject
{
private:
	GSprite * _sprite_deadth;

	int HeartCollect; // số lượng item heart người chơi nhặt được
	int Lives; // số mạng của simon
	int score; // điểm

	bool isFreeze; // Trạng thái đóng băng thay đổi màu liên tục
	DWORD TimeFreeze; // thời gian đã đóng băng

	D3DXVECTOR2 PositionBackup;


	bool isWalking_Backup;
	bool isJumping_Backup;
	bool isSitting_Backup;
	bool isAttacking_Backup;
	bool isOnStair_Backup;
	int isProcessingOnStair_Backup;
	int directionStair_Backup;
	int directionY_Backup;
	int directionAfterGo;

	float AutoGoX_Distance; // khoảng cách simon cần tự đi
	float AutoGoX_Speed; // vận tốc đi tự động
	float AutoGoX_DirectionGo; // hướng tự động đi
	float AutoGoX_Backup_X; // lưu vị trí trước khi đi tự động

	bool isAutoGoX = 0; // đang ở chế độ auto go?

	bool isDeadth;
	 
	eType TypeWeaponCollect; // loại vũ khí phụ đang giữ
	
	Camera * camera;
	Sound * sound;
	bool isUseDoubleShot;


public:
	bool isWalking;
	bool isJumping;
	bool isSitting;
	bool isAttacking;
	bool isHurting;

	bool isOnStair;
	int isProcessingOnStair;  // có 2 giai đoạn 
	int directionStair; // hướng của cầu thang đang đi, -1 đi qua trái, 1 đi qua phải
	int directionY; // hướng đi theo trục y của simon
	 
	float DoCaoDiDuoc = 0;

	bool untouchable;
	DWORD untouchable_start;
	 
	bool isCollisionAxisYWithBrick = false; // Đang va chạm với đất theo trục y
	 
	DWORD TimeWaitedAfterDeath;


public:
	Simon(Camera* camera);
	~Simon();
	  
	unordered_map<eType, Weapon*> mapWeapon;
	  
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera);
	void Left();  // set lại hướng của simon
	void Right(); // set lại hướng của simon
	void Go();
	
	void Sit();
	void ResetSit();

	void Jump();
	void Stop();

	void SetHurt(LPCOLLISIONEVENT e);

	void SetHeartCollect(int h);
	int GetHeartCollect();

	void CollisionWithBrick(const vector<LPGAMEOBJECT> *coObjects = NULL);
 
	void CollisionIsOnStair(vector<LPGAMEOBJECT> *coObjects = NULL);
	bool isCollisionWithItem(Item * objItem);


	void Attack(eType typeWeapon);

	int GetLives();
	void SetLives(int l);
	int GetScore();
	void SetScore(int s);

	bool GetFreeze();
	void SetFreeze(int f);
	void UpdateFreeze(DWORD dt);

	void StartUntouchable();



	void SetAutoGoX(int DirectionGo, int DirectionBackup, float Dx, float Speed); // set các thông số auto và backup các trạng thái hiện tại
	bool GetIsAutoGoX(); // kiểm tra có đang ở chế độ auto go?

	void RestoreBackupAutoGoX(); // khôi phục trạng thái 

	bool LoseLife(); // thiết lập lại 1 số thứ sau khi simon mất mạng
	void SetPositionBackup(float X, float Y);  // lưu vị trí cần backup để simon die thì bắt đầu lại từ đây


	void SetDeadth();
	bool GetIsDeadth();
	void SetIsDeadth(bool b);


	eType GetTypeWeaponCollect();
	void SetTypeWeaponCollect(eType t);
	void ProcessWeaponCollect(eType t);
	bool IsUsingWeapon(eType typeWeapon);

	bool GetIsUseDoubleShot();
	void SetIsUseDoubleShot(bool b);

	void Init(); // khởi tạo lại các trạng thái, HeartCollect, Heath, Lives, Score
	void Reset(); // khởi tạo lại các trạng thái.

};






#endif