#ifndef __SCENE_H__
#define __SCENE_H__


#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"


#include "Mario.h"
#include "Brick.h"
#include "Goomba.h"

#include "Simon.h"
#include "define.h"
#include "Map.h"
#include "Camera.h"
#include "Grid.h"
#include "Item.h"

class Scene
{ 


	

public:
	static Scene * __Instance;
	vector <Scene*> listScene;

	Scene();
	~Scene();

	static Scene* GetInstance();

	void LoadResources();
	void Update(DWORD dt);
	void Render();
	void ChangeScene(Scene * scene);

};



#endif // !__SCENE_H__

