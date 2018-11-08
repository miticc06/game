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




class Scene_1 : public Scene
{
public:

	Simon * simon;
	Map * TileMap;
	Camera *camera;
	Grid * gridGame;

	Board * board;

	VariableGlobal * _variableGlobal;


	vector<LPOBJECT> ListObj;



public:
	Scene_1();
	~Scene_1();

	void KeyState(BYTE *state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);

	void LoadResources();
	void Update(DWORD dt);
	void Render();

};

#endif