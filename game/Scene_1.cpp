#include "Scene_1.h"



Scene_1::Scene_1()
{
}


Scene_1::~Scene_1()
{
}

void Scene_1::KeyState(BYTE * state)
{
	
	//simon->Jump();

	//return;

	if (simon->isJumping && simon->isWalking)
		return;

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
	
	if (simon->isJumping)
		return;

	if (Game::GetInstance()->IsKeyDown(DIK_RIGHT))
	{
		if (simon->isAttacking)
		{
			float vx, vy;
			simon->GetSpeed(vx, vy);
			simon->SetSpeed(0, vy);
			return;
		}
			
		simon->Right();
		simon->Go();
	}
	else
		if (Game::GetInstance()->IsKeyDown(DIK_LEFT))
		{
			if (simon->isAttacking)
			{
				float vx, vy;
				simon->GetSpeed(vx, vy);
				simon->SetSpeed(0, vy);
				return;
			}
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



	if (KeyCode == DIK_1)
	{
		DebugOut(L"[SIMON] X = %f , Y = %f \n", simon->GetX() + 10, simon->GetY());
	}

	if (KeyCode == DIK_X)
	{
		//DebugOut(L"[SIMON] X = %f , Y = %f \n", simon->x + 10, simon->y);
		simon->Attack(simon->_ListWeapon[0]);
	}

	if (simon->isJumping && simon->isWalking)
	{
		return;
	}
	
	


 
	if (KeyCode == DIK_SPACE)
	{
		if (Game::GetInstance()->IsKeyDown(DIK_LEFT) || Game::GetInstance()->IsKeyDown(DIK_RIGHT))
		{
			simon->Stop();
			float vx, vy;
			simon->GetSpeed(vx, vy);
			simon->SetSpeed(SIMON_WALKING_SPEED * simon->GetTrend()/**vx - 0.0001f*/,vy - SIMON_VJUMP);
			simon->isJumping = 1;
			simon->isWalking = 1;
		}
		else
		{
			//simon->Stop();
			//float vx, vy;
			//simon->GetSpeed(vx, vy);
			//simon->SetSpeed(0,/* vy - SIMON_VJUMP*/ -1.4f);
			//simon->isJumping = 1;

			simon->Jump();
		}


		
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

	simon = new Simon();
	TileMap = new Map();
	camera = new Camera(Window_Width, Window_Height/*, Window_Width/2, MapWidth - Window_Width / 2*/);
	camera->SetPosition(0, 0);


	board = new Board(0, 0);

	simon->SetPosition(SIMON_POSITION_DEFAULT);
	//simon->SetPosition(0, 0);


	gridGame = new Grid();
	gridGame->ReadFileToGrid("Resources\\map\\Obj_1.txt"); // đọc các object từ file vào Grid

	listItem.clear();


 
}

void Scene_1::Update(DWORD dt)
{
//	DebugOut(L"[DT] DT: %d\n", dt);

	gridGame->GetListObject(listObj, camera); // lấy hết các object trong vùng camera;
	DebugOut(L"[Grid] ListObject by Camera = %d\n", listObj.size());



	simon->Update(dt, &listObj);
	camera->SetPosition(simon->GetX() - Window_Width / 2 + 30, camera->GetYCam()); // cho camera chạy theo simon
	camera->Update();

	for (UINT i = 0; i < listObj.size(); i++)
	{
		listObj[i]->Update(dt, &listObj);
	}

	for (UINT i = 0; i < listItem.size(); i++)
		listItem[i]->Update(dt, &listObj); // trong các hàm update chỉ kiểm tra va chạm với đất
	 

	CheckCollision();

}





void Scene_1::Render()
{

	TileMap->DrawMap(camera);


	for (UINT i = 0; i < listObj.size(); i++)
		listObj[i]->Render(camera);

	for (UINT i = 0; i < listItem.size(); i++)
		listItem[i]->Render(camera);
	 
	simon->Render(camera);


	board->Render(camera, simon, 1);



}

void Scene_1::CheckCollision()
{
	if (simon->_ListWeapon[0]->GetFinish()==false) // Vũ khí đang hoạt động
		CheckCollisionWeapon();

	CheckCollisionSimonWithItem();


}

void Scene_1::CheckCollisionWeapon()
{
	for (UINT i = 0; i < listObj.size(); i++)
		if (listObj[i]->GetType() == eID::TORCH)
			if (simon->_ListWeapon[0]->isCollision(listObj[i]) == true)
			{
				GameObject *gameObjTorch = dynamic_cast<GameObject*>(listObj[i]);
				gameObjTorch->SubHealth(1);
				listItem.push_back(GetNewItem(gameObjTorch->GetId(), eID::TORCH, gameObjTorch->GetX(), gameObjTorch->GetY()));
			}




}

void Scene_1::CheckCollisionSimonWithItem()
{
	for (UINT i = 0; i < listItem.size(); i++)
		if (listItem[i]->GetFinish() == false)
		{
			if (simon->isCollisionWithItem(listItem[i]) == true) // có va chạm
			{
				switch (listItem[i]->GetType())
				{
				case eID::LARGEHEART:
				{
					simon->SetHeartCollect(simon->GetHeartCollect() + 5);
					listItem[i]->SetFinish(true);
					break;
				} 
				case eID::UPGRADEMORNINGSTAR:
				{
					MorningStar * objMorningStar = dynamic_cast<MorningStar*>(simon->_ListWeapon[0]);
					objMorningStar->UpgradeLevel(); // Nâng cấp vũ khí roi
					listItem[i]->SetFinish(true);
					break;
				}
				default:
					DebugOut(L"[CheckCollisionSimonWithItem] Khong nhan dang duoc loai Item!\n");
					break;
				}

			}
		}





}




Item * Scene_1::GetNewItem(int Id, eID Type, float X, float Y)
{
	if (Type == eID::TORCH)
	{
		if (Id == 1 || Id == 4)
			return new LargeHeart(X, Y);

		if (Id == 2 || Id == 3)
			return new UpgradeMorningStar(X, Y);

		//	return new LargeHeart(X, Y);

	}

	return new LargeHeart(X, Y);
}