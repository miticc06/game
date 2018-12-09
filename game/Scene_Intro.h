#ifndef __SCENE_INTRO_H__
#define __SCENE_INTRO_H__

#include "Scene.h"
#include "TextureManager.h"
#include "Sound.h"
#include "GSprite.h"
#include "Font.h"

#define INTRO_STATUS_PROCESS_MENU 0 
#define INTRO_STATUS_PROCESS_GO_SCENE1 1 


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