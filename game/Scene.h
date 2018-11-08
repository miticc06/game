#ifndef __SCENE_H__
#define __SCENE_H__
 

#include "define.h"

class Scene  
{
public:
	Scene();
	~Scene();


	virtual void KeyState(BYTE *state) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;

	virtual void LoadResources() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
	
};

#endif