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
#define GAME_TIME_SCENE2 300

#define TIME_DISTANCE_CREATE_GHOST 1000 // 1 giây

class Scene_2 : public Scene
{
private:
	
	int CountEnemyGhost; // số lượng ghost hiện tại
	DWORD TimeCreateGhost; // thời điêm đã tạo ghost trước đó



	Simon * simon;
	Map * TileMap;
	Camera *camera;
	Grid * gridGame;
	Board * board;
	Sound * sound;

	vector<LPOBJECT> listObj;

	vector <Item*> listItem;
	vector <Effect*> listEffect;
	vector <Enemy*> listEnemy;

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
	void CheckCollisionWeapon();
	void CheckCollisionSimonWithItem();
	void CheckCollisionSimonWithObjectHidden();

	Item * GetNewItem(int Id, eID Type, float X, float Y);
};



#endif