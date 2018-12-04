﻿#ifndef __SCENE_2_H__
#define __SCENE_2_H__


#include "Scene.h"
#include "Camera.h"
#include "GSprite.h"
#include "Brick.h"
#include "Simon.h" 
#include "Map.h"
#include "Camera.h"
#include "Grid.h"
#include "Item.h" 
#include "Board.h"
#include "ItemDagger.h"
#include "Dagger.h"
#include "TextureManager.h"
#include "Effect.h"
#include "Fire.h"
#include "Hit.h"
#include "GameTime.h"
#include "Sound.h"
#include "Bonus.h"
#include "SmallHeart.h"
#include "Enemy.h"
#include "Ghost.h"
#include "Panther.h"
#include "Bat.h"
#include "HolyWater.h"
#include "ItemHolyWater.h"
#include "BrokenBrick.h"
#include "PotRoast.h"
#include "StopWatch.h"
#include "ItemStopWatch.h"
#include "Fishmen.h"
#include "Steam.h"

#define GAME_TIME_SCENE2 300

#define ThoiGianChoGiua2GhostDuocTao 1000 // 1 giây - khoảng thời gian phải chờ giữa ghost đầu và ghost sẽ đưcọ tạo tiếp theo
#define ThoiGianChoDeXuLiTaoGhost 2500 // 2.5 giây
#define ViTriCameraDiChuyenTruocKhiQuaCua 2809.0f
#define ViTriCameraDiChuyenSauKhiQuaCua 3073.0f

#define BienPhaiCameraKhiChuaQuaCua1 2576.0f

#define REGION_CREATE_PANTHER_LEFT 1090.0f
#define REGION_CREATE_PANTHER_RIGHT 2305.0f

#define CAMERA_POSITION_Y_LAKE 374.0f
  
#define CAMERA_BOUNDARY_LAKE_LEFT 3075.0f
#define CAMERA_BOUNDARY_LAKE_RIGHT 4111.0f-Window_Width

#pragma region define FISHMEN

#define FISHMEN_ZONE_1_LEFT 3065
#define FISHMEN_ZONE_1_RIGHT 3193 
#define FISHMEN_POS_1 3121 

#define FISHMEN_ZONE_2_LEFT 3193
#define FISHMEN_ZONE_2_RIGHT 3326
#define FISHMEN_POS_2 3254 

#define FISHMEN_ZONE_3_LEFT 3326
#define FISHMEN_ZONE_3_RIGHT 3458
#define FISHMEN_POS_3 3382 

#define FISHMEN_ZONE_4_LEFT 3458
#define FISHMEN_ZONE_4_RIGHT 3571
#define FISHMEN_POS_4 3505 

#define FISHMEN_ZONE_5_LEFT 3571
#define FISHMEN_ZONE_5_RIGHT 3707
#define FISHMEN_POS_5 3636 

#define FISHMEN_ZONE_6_LEFT 3707
#define FISHMEN_ZONE_6_RIGHT 3829
#define FISHMEN_POS_6 3760 

#define FISHMEN_ZONE_7_LEFT 3829
#define FISHMEN_ZONE_7_RIGHT 3956
#define FISHMEN_POS_7 3881 


#define FISHMEN_ZONE_8_LEFT 3956
#define FISHMEN_ZONE_8_RIGHT 4095
#define FISHMEN_POS_8 4017 

#pragma endregion




class Scene_2 : public Scene
{
private:
	
	/*Xử lí liên quan tạo ghost*/
	int CountEnemyGhost; // số lượng ghost hiện tại
	DWORD TimeCreateGhost; // thời điểm bắt đầu tạo ghost
	DWORD TimeWaitProcessCreateGhost; // Thời điểm bắt đầu chờ xử lí việc tạo ghost
	bool isWaitProcessCreateGhost; // chờ xử lí việc tạo ghost
	bool isAllowCheckTimeWaitProcessCreateGhost = false; // cho phép kt thời gian chờ xử lí tạo ghost

	/*Xử lí liên quan đi qua cửa*/
	bool isProcessingGoThroughTheDoor1;
	bool isDoneSimonGoThroughTheDoor1; 
	bool isDoneCameraGoThroughTheDoor1;

	/*Xử lí liên quan tạo Panther*/
	bool isAllowRenewPanther;
	int CountEnemyPanther;


	/*Xử lí liên quan tạo Fishmen*/
	bool isAllowCreateFishmen;
	int CountEnemyFishmen;
	DWORD TimeCreateFishmen;
	DWORD TimeWaitCreateFishmen;

	/*Xử lí liên quan tạo Bat*/
	DWORD TimeCreateBat; // thời điểm đã tạo BAT
	DWORD TimeWaitCreateBat; // thời gian phải chờ để tạo bot
	bool isAllowCreateBat; // cho phép tạo Bat
	int CountEnemyBat;

	Simon * simon;
	Map * TileMap;
	Camera *camera;
	Grid * gridGame;
	Board * board;
	Sound * sound;

	vector<GameObject*> listObj;
	vector <Item*> listItem;
	vector <Effect*> listEffect;
	vector <GameObject*> listEnemy;
	
	vector <Weapon*> listWeaponOfEnemy; // list chứa các viên đạn của enemy

	GameTime * _gameTime;
	int StateCurrent;

	/*Xử lí stopWatch*/
	bool isStopWatch;

public:
	Scene_2(Simon * _si = NULL, GameTime* _ga = NULL);
	~Scene_2();

	void KeyState(BYTE *state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void LoadResources();
	void Update(DWORD dt);
	void Render();


	void ResetResource(); // reset lai resource khi simon mất 1 mạng


	void CheckCollision();
	void CheckCollisionWeapon(vector<GameObject*> listObj);
	void CheckCollisionSimonWithItem();
	void CheckCollisionSimonWithObjectHidden();
	void CheckCollisionWithEnemy();
	void CheckCollisionSimonWithEnemy();
	void CheckCollisionSimonWithGate();
	Item * GetNewItem(int Id, eType Type, float X, float Y);
};



#endif