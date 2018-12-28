#ifndef __SCENE_INTRO_H__
#define __SCENE_INTRO_H__

#include "Scene.h"
#include "TextureManager.h"
#include "Sound.h"
#include "GSprite.h"
#include "Font.h"
#include "Simon.h"
#include "Board.h"
#include "Brick.h"
#include "HeliCopter.h"
#include "IntroBat.h"

#include "Scene_1.h"
#define INTRO_STATUS_PROCESS_MENU 0 
#define INTRO_STATUS_PROCESS_GO_SCENE1 1 

#define INTRO_SIMON_WALKING_SPEED 0.08f


class Scene_Intro : public Scene
{
private:
	GSprite* Sprite_MainMenu;
	GSprite* Sprite_IntroBatMenu;
	Sound * sound;
	Font TextPressStart;

	/*Xử lí nhấn phím thì tiếp tục*/
	bool isPressStart;
	DWORD TimeWaited; 

	/* Xử lí nhấp nháy TextPressStart */
	bool isDrawTextPressStart;
	DWORD TimeWaitedToChangeDisplayTextPressStart;
	 
	int StatusProcess;
	
	Simon * simon;
	Board * board;
	GSprite* Sprite_IntroGoScene1;
	Camera * camera;

	vector<LPGAMEOBJECT> listBrick; 

	HeliCopter * heliCopter;
	IntroBat * introBat1;
	IntroBat * introBat2;
public:
	Scene_Intro();
	virtual ~Scene_Intro();

	void KeyState(BYTE *state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void LoadResources();
	void Update(DWORD dt);
	void Render();


};


#endif