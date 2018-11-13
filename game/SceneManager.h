#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "Scene.h" 

#include "define.h" 

class SceneManager
{
private:
	static SceneManager * _Instance;

	Scene * _scene;

//	bool isNotLoadResource; // kt chưa load resource. dùng cho thay đổi scene

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

	//void SetIsNotLoadResource(bool b);

	Scene * GetScene();

};







#endif 