#ifndef __SCENE_2_H__
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
#include "Monney.h"
#include "SmallHeart.h"
#include "Enemy.h"
#include "Ghost.h"
#include "Panther.h"
#include "Bat.h"
#include "HolyWater.h"
#include "ItemHolyWater.h"


#define GAME_TIME_SCENE2 300

#define ThoiGianChoGiua2GhostDuocTao 1000 // 1 giây - khoảng thời gian phải chờ giữa ghost đầu và ghost sẽ đưcọ tạo tiếp theo
#define ThoiGianChoDeXuLiTaoGhost 2500 // 2.5 giây
#define ViTriCameraDiChuyenTruocKhiQuaCua 2809.0f
#define ViTriCameraDiChuyenSauKhiQuaCua 3073.0f

#define BienPhaiCameraKhiChuaQuaCua1 2576.0f

#define REGION_CREATE_PANTHER_LEFT 1090.0f
#define REGION_CREATE_PANTHER_RIGHT 2305.0f



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

	/*Xử lí liên quan tạo Bat*/
	DWORD TimeCreateBat; // thời điểm đã tạo BAT
	DWORD TimeWaitCreateBat; // thời gian phải chờ để tạo bot
	bool isAllowCreateBat; // cho phép tạo Bat


	bool isAllRenewBat;

	int CountEnemyBat;

	Simon * simon;
	Map * TileMap;
	Camera *camera;
	Grid * gridGame;
	Board * board;
	Sound * sound;

	vector<Object*> listObj;
	vector <Item*> listItem;
	vector <Effect*> listEffect;
	vector <Object*> listEnemy;
	 

	GameTime * _gameTime;


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
	void CheckCollisionWeapon(vector<Object*> listObj);
	void CheckCollisionSimonWithItem();
	void CheckCollisionSimonWithObjectHidden();
	void CheckCollisionWithEnemy();
	void CheckCollisionSimonWithEnemy();
	void CheckCollisionSimonWithGate();
	Item * GetNewItem(int Id, eID Type, float X, float Y);
};



#endif