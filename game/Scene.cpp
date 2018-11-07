#include "Scene.h"

Scene * Scene::__Instance = NULL;


Scene::Scene()
{
	listScene.clear();
}


Scene::~Scene()
{
}

Scene * Scene::GetInstance()
{
	if (__Instance == NULL)
		__Instance = new Scene();
	return __Instance;
}

void Scene::LoadResources()
{
	listScene.back()->LoadResources(); 
}

void Scene::Update(DWORD dt)
{
	listScene.back()->Update(dt);
}

void Scene::Render()
{
	listScene.back()->Render();
}

void Scene::ChangeScene(Scene * scene)
{
	Scene * Scene_current = listScene.back();
	listScene.pop_back();
	SAFE_DELETE(Scene_current);


	listScene.push_back(scene);
}
