#include "Scene_1.h"



Scene_1::Scene_1()
{
}


Scene_1::~Scene_1()
{
}

void Scene_1::KeyState(BYTE * state)
{
 
	if (Game::GetInstance()->IsKeyDown(DIK_DOWN))
	{
		simon->Sit();

		if (Game::GetInstance()->IsKeyDown(DIK_RIGHT))
			simon->Right();

		if (Game::GetInstance()->IsKeyDown(DIK_LEFT))
			simon->Left();

		return;
	}
	else
		simon->Stop();


	if (Game::GetInstance()->IsKeyDown(DIK_RIGHT))
	{
		simon->Right();
		simon->Go();
	}
	else
		if (Game::GetInstance()->IsKeyDown(DIK_LEFT))
		{
			simon->Left();
			simon->Go();
		}
		else
		{
			simon->Stop();
		}
  

}

void Scene_1::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	if (KeyCode == DIK_ESCAPE)
		DestroyWindow(/*hWnd*/ Game::GetInstance()->GetWindowHandle()); // thoát

	if (KeyCode == DIK_Q)
		simon->SetPosition(SIMON_POSITION_DEFAULT);

	if (KeyCode == DIK_SPACE)
	{
		simon->Jump();
	}

	if (KeyCode == DIK_1)
	{
		DebugOut(L"[SIMON] X = %f , Y = %f \n", simon->GetX() + 10, simon->GetY());
	}

	if (KeyCode == DIK_X)
	{
		//DebugOut(L"[SIMON] X = %f , Y = %f \n", simon->x + 10, simon->y);
		simon->Attack(simon->_ListWeapon[0]);
	}
}

void Scene_1::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	switch (KeyCode)
	{
	case DIK_SPACE:
		//simon->Sit();
		break;
	}
}

void Scene_1::LoadResources()
{

	//_variableGlobal = VariableGlobal::GetInstance();


	simon = new Simon();
	TileMap = new Map();
	camera = new Camera(Window_Width, Window_Height/*, Window_Width/2, MapWidth - Window_Width / 2*/);
	camera->SetPosition(0, 0);


	board = new Board(0, 0);

	simon->SetPosition(SIMON_POSITION_DEFAULT);
	simon->SetPosition(0, 0);


	gridGame = new Grid();
	gridGame->ReadFileToGrid("Resources\\map\\Obj_1.txt"); // đọc các object từ file vào Grid




	//_variableGlobal->ListItem.clear();

}

void Scene_1::Update(DWORD dt)
{
	DebugOut(L"[DT] DT: %d\n", dt);


	gridGame->GetListObject(ListObj, camera); // lấy hết các object trong vùng camera;

	simon->Update(dt, &ListObj);
	camera->SetPosition(simon->GetX() - Window_Width / 2 + 30, camera->GetYCam()); // cho camera chạy theo simon
	camera->Update();

	for (UINT i = 0; i < ListObj.size(); i++)
	{
		ListObj[i]->Update(dt, &ListObj);
	}

	//for (UINT i = 0; i < _variableGlobal->ListItem.size(); i++) // update các Item
	//{
	//	_variableGlobal->ListItem[i]->Update(dt, &ListObj);
	//}
}

void Scene_1::Render()
{

	TileMap->DrawMap(camera);


	for (UINT i = 0; i < ListObj.size(); i++)
		ListObj[i]->Render(camera);

	 

	//for (UINT i = 0; i < _variableGlobal->ListItem.size(); i++) // Draw các item
	//	_variableGlobal->ListItem[i]->Render(camera);




	board->Render(camera);

	simon->Render(camera);


}
