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
//	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	if (KeyCode == DIK_ESCAPE)
		DestroyWindow(/*hWnd*/ Game::GetInstance()->GetWindowHandle()); // thoát

	if (KeyCode == DIK_Q)
		simon->SetPosition(SIMON_POSITION_DEFAULT);



	if (KeyCode == DIK_1)
	{
		DebugOut(L"[SIMON] X = %f , Y = %f \n", simon->GetX() + 10, simon->GetY());
	}




	if (KeyCode == DIK_2) // lấy tọa độ world của chuột 
	{
		POINT p;
		GetCursorPos(&p);
  		ScreenToClient(Game::GetInstance()->GetWindowHandle(), &p);
		DebugOut(L"[MOUSE POSITION] x: %d , y = %d\n", p.x + (int)camera->GetXCam(), p.y+ (int)camera->GetYCam());

	}







	if (KeyCode == DIK_X)
	{
		//DebugOut(L"[SIMON] X = %f , Y = %f \n", simon->x + 10, simon->y);
		simon->Attack(simon->_weaponMain);
	}


	if (KeyCode == DIK_Z)
	{
		if (simon->_weaponSub != NULL && simon->_weaponSub->GetFinish() == true && simon->GetHeartCollect()>0)
		{
			simon->SetHeartCollect(simon->GetHeartCollect() - 1); // giảm 1 heart
			simon->Attack(simon->_weaponSub);
		}
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
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	switch (KeyCode)
	{
	case DIK_SPACE:
		//simon->Sit();
		break;
	}
}

void Scene_1::LoadResources()
{ 
	TextureManager * _textureManager = TextureManager::GetInstance(); // Đã gọi load resource

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
	listEffect.clear();

	_gameTime.SetTime(0); // đếm lại từ 0
}

void Scene_1::Update(DWORD dt)
{
//	DebugOut(L"[DT] DT: %d\n", dt);

	if (_gameTime.GetTime() >= GAME_TIME_SCENE1)
	{
	//	DebugOut(L"Het thoi gian! %d \n", GetTickCount());
		return;
	}
	else
		_gameTime.Update();


	gridGame->GetListObject(listObj, camera); // lấy hết các object "còn Alive" trong vùng camera;
	//DebugOut(L"[Grid] ListObject by Camera = %d\n", listObj.size());

	 

	simon->Update(dt, &listObj);

	camera->SetPosition(simon->GetX() - Window_Width / 2 + 30, camera->GetYCam()); // cho camera chạy theo simon
	camera->Update();

	for (UINT i = 0; i < listObj.size(); i++)
		listObj[i]->Update(dt, &listObj);  // đã kiểm tra "Alive" lúc lấy từ lưới ra

	for (UINT i = 0; i < listItem.size(); i++)
		if (listItem[i]->GetFinish()== false)
			listItem[i]->Update(dt, &listObj); // trong các hàm update chỉ kiểm tra va chạm với đất


	for (UINT i = 0; i < listEffect.size(); i++)
		if (listEffect[i]->GetFinish() == false)
			listEffect[i]->Update(dt);


	CheckCollision();

}





void Scene_1::Render()
{

	TileMap->DrawMap(camera);


	for (UINT i = 0; i < listObj.size(); i++)
		listObj[i]->Render(camera);

	for (UINT i = 0; i < listItem.size(); i++)
		if (listItem[i]->GetFinish()==false)
			listItem[i]->Render(camera);
	 
	for (UINT i = 0; i < listEffect.size(); i++)
		if (listEffect[i]->GetFinish() == false)
			listEffect[i]->Render(camera);

	simon->Render(camera);

	board->Render(camera, simon, 1, simon->_weaponSub, GAME_TIME_SCENE1 - _gameTime.GetTime());



}

void Scene_1::CheckCollision()
{
	CheckCollisionWeapon();

	CheckCollisionSimonWithItem();


}

void Scene_1::CheckCollisionWeapon()
{
	// main weapon
	if (simon->_weaponMain->GetFinish() == false) // Vũ khí đang hoạt động
	{
		for (UINT i = 0; i < listObj.size(); i++)
			if (listObj[i]->GetType() == eID::TORCH)
				if (simon->_weaponMain->isCollision(listObj[i]) == true)
				{
					GameObject *gameObjTorch = dynamic_cast<GameObject*>(listObj[i]);
					gameObjTorch->SubHealth(1);

					listEffect.push_back(new Hit(gameObjTorch->GetX()+14, gameObjTorch->GetY() + 14)); // hiệu ứng lửa
					listEffect.push_back(new Fire(gameObjTorch->GetX() - 5, gameObjTorch->GetY()+8)); // hiệu ứng lửa
					listItem.push_back(GetNewItem(gameObjTorch->GetId(), eID::TORCH, gameObjTorch->GetX() +5, gameObjTorch->GetY()));
				}
	}


	// subweapon
	if (simon->_weaponSub != NULL && simon->_weaponSub->GetFinish() == false)
	{
		for (UINT i = 0; i < listObj.size(); i++)
			if (listObj[i]->GetType() == eID::TORCH)
				if (simon->_weaponSub->isCollision(listObj[i]) == true)
				{
					GameObject *gameObjTorch = dynamic_cast<GameObject*>(listObj[i]);

					gameObjTorch->SubHealth(1);

					simon->_weaponSub->SetFinish(true);   // cây kiếm trúng object thì tắt luôn

					listEffect.push_back(new Hit(gameObjTorch->GetX() + 14, gameObjTorch->GetY() + 14)); // hiệu ứng lửa
					listEffect.push_back(new Fire(gameObjTorch->GetX() - 5, gameObjTorch->GetY() + 8)); // hiệu ứng lửa
					listItem.push_back(GetNewItem(gameObjTorch->GetId(), eID::TORCH, gameObjTorch->GetX() + 5, gameObjTorch->GetY()));
				}
	}



}

void Scene_1::CheckCollisionSimonWithItem()
{
	for (UINT i = 0; i < listItem.size(); i++)
		if (listItem[i]->GetFinish() == false && listItem[i]->isWaitingDisplay() == false) // chưa kết thúc và "không phải" đang chờ để hiển thị
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
					MorningStar * objMorningStar = dynamic_cast<MorningStar*>(simon->_weaponMain);
					objMorningStar->UpgradeLevel(); // Nâng cấp vũ khí roi
					listItem[i]->SetFinish(true);
					break;
				}
 
				case eID::ITEMDAGGER:
				{
					SAFE_DELETE(simon->_weaponSub);
					simon->_weaponSub = new Dagger();
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

		if (Id == 5)
			return new ItemDagger(X, Y);

	}

	return new LargeHeart(X, Y);
}