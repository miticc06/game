#include "Scene_1.h"



Scene_1::Scene_1()
{  
	LoadResources();
}


Scene_1::~Scene_1()
{
	SAFE_DELETE(TileMap);
	SAFE_DELETE(board);
	SAFE_DELETE(gridGame); 

}

void Scene_1::KeyState(BYTE * state)
{
	if (simon->GetFreeze() == true) // Đang bóng băng thì không quan tâm phím
	{
		return;
	}



	if (simon->GetIsAutoGoX() == true) // đang chế độ tự đi thì ko xét phím
		return;


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
	if (simon->GetFreeze() == true) // Đang bóng băng thì không quan tâm phím
	{
		return;
	}

	// chưa xét khi hết time hoặc die thì sao?




//	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	if (KeyCode == DIK_ESCAPE)
		DestroyWindow(/*hWnd*/ Game::GetInstance()->GetWindowHandle()); // thoát

	if (KeyCode == DIK_Q)
		simon->SetPosition(SIMON_POSITION_DEFAULT);



	if (KeyCode == DIK_1) // vị trí simon
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


	if (KeyCode == DIK_3) // set vi tri simon 1275 
	{ 
		DebugOut(L"[SET POSITION SIMON] x = 1275 \n");
		simon->SetPosition(1275.0f, 0);
	}




	if (KeyCode == DIK_P) // tesst autogo 
	{
		simon->SetAutoGoX(simon->GetDirection(), simon->GetDirection(), 200, SIMON_WALKING_SPEED);
	}





	if (simon->GetIsAutoGoX() == true) // đang chế độ tự đi thì ko xét phím
		return;





	if (KeyCode == DIK_X)
	{
		//DebugOut(L"[SIMON] X = %f , Y = %f \n", simon->x + 10, simon->y);

		if (simon->isAttacking == false)
			sound->Play(eSound::soundWhip);

		simon->Attack(simon->_weaponMain);

	}


	if (KeyCode == DIK_Z)
	{
		if (simon->_weaponSub != NULL && simon->_weaponSub->GetFinish() == true && simon->GetHeartCollect()>0)
		{
			simon->SetHeartCollect(simon->GetHeartCollect() - 1); // giảm 1 heart
			simon->Attack(simon->_weaponSub);
			sound->Play(eSound::soundDagger);
		}
	}

	if (simon->isJumping && simon->isWalking)
	{
		return;
	}
	
	


 
	if (KeyCode == DIK_SPACE && simon->isOnStair == false)
	{
		if (Game::GetInstance()->IsKeyDown(DIK_LEFT) || Game::GetInstance()->IsKeyDown(DIK_RIGHT))
		{
			simon->Stop();
			simon->SetSpeed(SIMON_WALKING_SPEED * simon->GetDirection(), -SIMON_VJUMP);
			simon->isJumping = 1;
			simon->isWalking = 1;
		}
		else
		{
			simon->Jump();
		}
	}

}

void Scene_1::OnKeyUp(int KeyCode)
{
	if (simon->GetFreeze() == true) // Đang bóng băng thì không quan tâm phím
	{
		return;
	}

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
	sound = Sound::GetInstance();

	simon = new Simon();
	TileMap = new Map();
	TileMap->LoadMap(eType::MAP1);

	camera = SceneManager::GetInstance()->GetCamera();

	camera->SetBoundary(0, TileMap->GetMapWidth() - camera->GetWidth()); // set biên camera dựa vào kích thước map
	camera->SetBoundaryBackup(camera->GetBoundaryLeft(), camera->GetBoundaryRight()); // backup lại biên

	camera->SetPosition(0, 0);


	board = new Board(BOARD_DEFAULT_POSITION_X, BOARD_DEFAULT_POSITION_Y);

	simon->SetPosition(SIMON_POSITION_DEFAULT);
	simon->SetPositionBackup(SIMON_POSITION_DEFAULT);

	gridGame = new Grid();
	gridGame->ReadFileToGrid("Resources\\map\\Obj_1.txt"); // đọc các object từ file vào Grid



	listItem.clear();
	listEffect.clear();

	_gameTime = new GameTime();
	_gameTime->SetTime(0); // đếm lại từ 0

	 
	// bật nhạc game
	sound->Play(eSound::musicState1, true);
	 
}

void Scene_1::Update(DWORD dt)
{
	if (simon->GetFreeze() == true)
	{
		simon->UpdateFreeze(dt);
		if (simon->GetFreeze() == true)
			return;
	}


	if (_gameTime->GetTime() >= GAME_TIME_SCENE1) // hết thời gian
	{
		sound->Play(eSound::musicLifeLost);
		if (simon->GetLives() == 0)
			return;
		bool result = simon->LoseLife();
		if (result == true) // còn mạng để chơi tiếp, giảm mạng reset máu xong
		{
			ResetResource(); // reset lại game
		}
		return;
	}
	else
		_gameTime->Update(dt);



	if (GAME_TIME_SCENE1 - _gameTime->GetTime() <= 30 ) // đúng còn lại 30 giây thì bật sound loop
	{
		if (_gameTime->CheckIsJustChanged() == true) // Kiểm tra _time vừa thay đổi thì mới play nhạc. Nếu chỉ kt <=30s thì cứ mỗi deltatime nó sẽ Play nhạc -> thừa, ko đều
		{
			sound->Play(eSound::soundStopTimer);
		}
	}


	gridGame->GetListObject(listObj, camera); // lấy hết các object "còn Alive" trong vùng camera;
	//DebugOut(L"[Grid] ListObject by Camera = %d\n", listObj.size());
	DebugOut(L"[GRID] size = %d\n", listObj.size());


	simon->Update(dt, camera, &listObj);

	if (camera->AllowFollowSimon())
	{
		camera->SetPosition(simon->GetX() - Window_Width / 2 + 30, camera->GetYCam()); // cho camera chạy theo simon
	} 
	camera->Update(dt);

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
 
	board->Render(simon, 1, simon->_weaponSub, GAME_TIME_SCENE1 - _gameTime->GetTime(), NULL);



}

void Scene_1::ResetResource()
{
	SAFE_DELETE(gridGame);
	gridGame = new Grid();
	gridGame->ReadFileToGrid("Resources/map/Obj_1.txt"); // đọc lại các object từ list

	listItem.clear();
	listEffect.clear();

	_gameTime->SetTime(0); // đếm lại từ 0
	sound->Stop(eSound::musicState1); // tắt nhạc nền
	sound->Play(eSound::musicState1, true); // mở lại nhạc nền
}

void Scene_1::CheckCollision()
{
	CheckCollisionWeapon();

	CheckCollisionSimonWithItem();

	CheckCollisionSimonWithObjectHidden();
}

void Scene_1::CheckCollisionWeapon()
{
	// main weapon
	if (simon->_weaponMain->GetFinish() == false) // Vũ khí đang hoạt động
	{
		for (UINT i = 0; i < listObj.size(); i++)
			if (listObj[i]->GetType() == eType::TORCH)
				if (simon->_weaponMain->isCollision(listObj[i]) == true)
				{
					GameObject *gameObjTorch = listObj[i];
					gameObjTorch->SubHealth(1);

					listEffect.push_back(new Hit((int)gameObjTorch->GetX()+14, (int)gameObjTorch->GetY() + 14)); // hiệu ứng Hit
					listEffect.push_back(new Fire((int)gameObjTorch->GetX() - 5, (int)gameObjTorch->GetY()+8)); // hiệu ứng lửa
					
					listItem.push_back(GetNewItem(gameObjTorch->GetId(), gameObjTorch->GetType(), gameObjTorch->GetX() +5, gameObjTorch->GetY()));

					sound->Play(eSound::soundHit);
				}
	}


	// subweapon
	if (simon->_weaponSub != NULL && simon->_weaponSub->GetFinish() == false)
	{
		for (UINT i = 0; i < listObj.size(); i++)
			if (listObj[i]->GetType() == eType::TORCH)
				if (simon->_weaponSub->isCollision(listObj[i]) == true)
				{
					GameObject *gameObjTorch = listObj[i] ;

					gameObjTorch->SubHealth(1);

					simon->_weaponSub->SetFinish(true);   // cây kiếm trúng object thì tắt luôn

					listEffect.push_back(new Hit((int)gameObjTorch->GetX() + 14, (int)gameObjTorch->GetY() + 14)); // hiệu ứng hit
					listEffect.push_back(new Fire((int)gameObjTorch->GetX() - 5, (int)gameObjTorch->GetY() + 8)); // hiệu ứng lửa
					listItem.push_back(GetNewItem(gameObjTorch->GetId(), gameObjTorch->GetType(), gameObjTorch->GetX() + 5, gameObjTorch->GetY()));

					sound->Play(eSound::soundHit);

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

				case eType::LARGEHEART:
				{
					simon->SetHeartCollect(simon->GetHeartCollect() + 5);
					listItem[i]->SetFinish(true);
					sound->Play(eSound::soundCollectItem);
					break;
				}  

				case eType::UPGRADEMORNINGSTAR:
				{
					MorningStar * objMorningStar = dynamic_cast<MorningStar*>(simon->_weaponMain);
					objMorningStar->UpgradeLevel(); // Nâng cấp vũ khí roi
					listItem[i]->SetFinish(true);
					simon->SetFreeze(true); // bật trạng thái đóng băng
					sound->Play(eSound::soundCollectWeapon);
					break;
				}
 
				case eType::ITEMDAGGER:
				{
					SAFE_DELETE(simon->_weaponSub);
					simon->_weaponSub = new Dagger(camera);
 					listItem[i]->SetFinish(true);
					sound->Play(eSound::soundCollectWeapon);
					break;
				}

				case eType::BONUS:
				{
					listItem[i]->SetFinish(true);
					sound->Play(eSound::soundCollectItem);
					simon->SetScore(simon->GetScore() + 1000);
					break;
				}
				 
				default:
					DebugOut(L"[CheckCollisionSimonWithItem] Khong nhan dang duoc loai Item!\n");
					break;
				} 
			}
		}





}

void Scene_1::CheckCollisionSimonWithObjectHidden()
{
	for (UINT i = 0; i < listObj.size(); i++)
	{
		if (listObj[i]->GetType() == eType::OBJECT_HIDDEN)
		{
			GameObject * gameObject = listObj[i];
			if (gameObject->GetHealth() > 0)
			{ 
				if (simon->isCollitionObjectWithObject(gameObject))
				{
					switch (gameObject->GetId())
					{
					case 7: // đụng trúng cửa
					{
						 
						SceneManager::GetInstance()->SetScene(new Scene_2(simon, _gameTime));

						return;
						break;
					}

					case 8:
					{
						sound->Play(eSound::soundDisplayMonney);
						listItem.push_back(GetNewItem(gameObject->GetId(), gameObject->GetType(), simon->GetX(), simon->GetY()));
						// chưa hiện effect 1000d
						

						break;
					}
					}


					gameObject->SubHealth(1); 

				}
			}
		}
	}
}




Item * Scene_1::GetNewItem(int Id, eType Type, float X, float Y)
{
	if (Type == eType::TORCH)
	{
		if (Id == 1 || Id == 4)
			return new LargeHeart(X, Y);

		if (Id == 2 || Id == 3)
			return new UpgradeMorningStar(X, Y);

		if (Id == 5)
			return new ItemDagger(X, Y);
	}

	if (Type == eType::OBJECT_HIDDEN)
	{
		if (Id == 8)
			return new Bonus(1240, 305);

	}

	return new LargeHeart(X, Y);
}