#ifndef __SCENE_1_H__
#define __SCENE_1_H__

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

class Scene_1 : public Scene
{
public:

	Simon * simon;
	Map * TileMap;
	Camera *camera;
	Grid * gridGame;
	Board * board;


	vector<LPOBJECT> listObj;

	vector <Item*> listItem;
	vector <Effect*> listEffect;


public:
	Scene_1();
	~Scene_1();

	void KeyState(BYTE *state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void LoadResources();
	void Update(DWORD dt);
	void Render();


	void CheckCollision();
	void CheckCollisionWeapon();
	void CheckCollisionSimonWithItem();

	Item * GetNewItem(int Id, eID Type, float X, float Y);
};

#endif