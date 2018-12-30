#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "Scene.h" 
#include "Camera.h"
#include "define.h" 

class SceneManager
{
private:
	static SceneManager * _Instance;
	Scene * _scene;
  
public:
	SceneManager();
	~SceneManager();


	static SceneManager * GetInstance();

	void SetScene(Scene * x); 

	void KeyState(BYTE *state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);

	void LoadResources();
	void Update(DWORD dt);
	void Render();

 
	Scene * GetScene();

};







#endif 