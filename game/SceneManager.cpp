#include "SceneManager.h"

SceneManager * SceneManager::_Instance = NULL;


SceneManager::SceneManager()
{
	camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);
}


SceneManager::~SceneManager()
{
}

SceneManager * SceneManager::GetInstance()
{
	if (_Instance == NULL)
		_Instance = new SceneManager();
	return _Instance;
}

void SceneManager::SetScene(Scene * x)
{
	Scene * scene_temp = _scene;
	
	// .....
	// có thể là truyền pointer simon cho Scene sau - quản lí điểm
	
	_scene = x;
	SAFE_DELETE(scene_temp);
}

 

void SceneManager::KeyState(BYTE * state)
{ 
	_scene->KeyState(state);
}

void SceneManager::OnKeyDown(int KeyCode)
{ 
	_scene->OnKeyDown(KeyCode);

}

void SceneManager::OnKeyUp(int KeyCode)
{ 
	_scene->OnKeyUp(KeyCode);

}

void SceneManager::LoadResources()
{
	_scene->LoadResources();

}

void SceneManager::Update(DWORD dt)
{ 
	_scene->Update(dt);
}

void SceneManager::Render()
{ 
	_scene->Render();
}

Camera * SceneManager::GetCamera()
{
	return camera;
}
 

Scene * SceneManager::GetScene()
{
	return _scene;
}
