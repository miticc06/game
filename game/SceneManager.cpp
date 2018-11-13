#include "SceneManager.h"

SceneManager * SceneManager::_Instance = NULL;


SceneManager::SceneManager()
{
	//isNotLoadResource = true;
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
	/*if (isNotLoadResource)
		return;*/
	_scene->KeyState(state);
}

void SceneManager::OnKeyDown(int KeyCode)
{
	/*if (isNotLoadResource)
		return;*/
	_scene->OnKeyDown(KeyCode);

}

void SceneManager::OnKeyUp(int KeyCode)
{
	/*if (isNotLoadResource)
		return;*/
	_scene->OnKeyUp(KeyCode);

}

void SceneManager::LoadResources()
{
	_scene->LoadResources();

}

void SceneManager::Update(DWORD dt)
{
	/*if (isNotLoadResource)
		return;*/
	_scene->Update(dt);
}

void SceneManager::Render()
{
	/*if (isNotLoadResource)
		return;*/
	_scene->Render();
}

//void SceneManager::SetIsNotLoadResource(bool b)
//{
//	isNotLoadResource = b;
//}

Scene * SceneManager::GetScene()
{
	return _scene;
}
