#include "Scene_2.h"



Scene_2::Scene_2(Simon * _si, GameTime* _ga)
{
	simon = _si;
	_gameTime = _ga;
	 
	LoadResources();

}


Scene_2::~Scene_2()
{
	SAFE_DELETE(TileMap);
	SAFE_DELETE(board);
	SAFE_DELETE(gridGame);
	SAFE_DELETE(camera);
}

void Scene_2::KeyState(BYTE * state)
{
	if (simon->GetFreeze() == true) // Đang bóng băng thì không quan tâm phím
	{
		return;
	}
	 
	if (simon->isAutoGoX == true) // đang chế độ tự đi thì ko xét phím
		return;

	if (simon->isJumping && simon->isWalking)
		return;


	if (!simon->isJumping)
	{


		if (Game::GetInstance()->IsKeyDown(DIK_UP))
		{
			if (!simon->isOnStair) // chưa trên thang
			{
				for (UINT i = 0; i < listObj.size(); i++)
					if (listObj[i]->GetType() == eID::STAIR_BOTTOM)
					{
						if (simon->isCollitionObjectWithObject(listObj[i])) // nếu va chạm với STAIR BOTOM
						{
							GameObject* gameobj = dynamic_cast<GameObject*>(listObj[i]);
							simon->trendStair = gameobj->GetTrend(); // lưu hướng của cầu thang đang đi vào simon
							simon->trendY = -1;// hướng đi lên
							simon->SetTrend(simon->trendStair);// hướng của simon khi đi lên là hướng của cầu thang

							simon->isOnStair = true; // set trạng thái đang trên cầu thang
							simon->DoCaoDiDuoc = 0; 

							if (simon->GetX() < gameobj->GetX())
							{
								simon->SetAutoGoX(1, gameobj->GetTrend(), gameobj->GetX() - simon->GetX(), SIMON_WALKING_SPEED);
								// hướng sau khi autogo phải là hướng của cầu thang:  gameobj->GetTrend()
							}
							else
								simon->SetAutoGoX(-1, gameobj->GetTrend(), simon->GetX() - gameobj->GetX(), SIMON_WALKING_SPEED);

							
							
							//simon->SetPosition(gameobj->GetX(), simon->GetY()); // đặt lại vị trí X của simon
							DebugOut(L"bat dau len cau thang!\n");


							return;
						}
					}
			}
			else // nếu đã trên cầu thang
			{
				DebugOut(L"Da o tren cau thang!\n");

				if (simon->isProcessingOnStair == 0 || simon->isProcessingOnStair == 3) // kết thúc xử lí trước đó
				{
					simon->isWalking = true;
					simon->isProcessingOnStair = 1;
					simon->trendY = -1;// hướng đi lên
					simon->SetTrend(simon->trendStair);// hướng của simon khi đi lên là hướng của cầu thang
					simon->SetSpeed(simon->GetTrend()* SIMON_SPEED_ONSTAIR, -1 * SIMON_SPEED_ONSTAIR);
				
					float vvx, vvy;
					simon->GetSpeed(vvx, vvy);
					DebugOut(L"vy = %f\n", vvy);
				}


			}
		}
		else
		{
			if (Game::GetInstance()->IsKeyDown(DIK_DOWN)) // ngược lại nếu nhấn nút xuống
			{
				if (!simon->isOnStair) // chưa trên cầu thang
				{
					int CountCollisionTop = 0;
					for (UINT i = 0; i < listObj.size(); i++)
						if (listObj[i]->GetType() == eID::STAIR_TOP)
						{
							if (simon->isCollitionObjectWithObject(listObj[i])) // nếu va chạm với STAIR TOP
							{
								GameObject* gameobj = dynamic_cast<GameObject*>(listObj[i]);
								simon->trendStair = gameobj->GetTrend(); // lưu hướng của cầu thang đang đi vào simon
								simon->trendY = 1;// hướng đi xuống
								simon->SetTrend(simon->trendStair);// hướng của simon khi đi xuống là hướng của cầu thang

								simon->isOnStair = true; // set trạng thái đang trên cầu thang
								simon->DoCaoDiDuoc = 0;


								if (simon->GetX() < gameobj->GetX())
								{
									simon->SetAutoGoX(1, - gameobj->GetTrend(), gameobj->GetX() - simon->GetX(), SIMON_WALKING_SPEED);
									// hướng sau khi autogo phải là hướng của cầu thang:  gameobj->GetTrend()
								}
								else
									simon->SetAutoGoX(-1, - gameobj->GetTrend(), simon->GetX() - gameobj->GetX(), SIMON_WALKING_SPEED);




							//	simon->SetPosition(gameobj->GetX(), simon->GetY());


								CountCollisionTop++;
								return;
							}
						}

					if (CountCollisionTop == 0) // ko đụng stair top, tức là ngồi bt
					{ 
						simon->Sit();
						if (Game::GetInstance()->IsKeyDown(DIK_RIGHT))
							simon->Right();

						if (Game::GetInstance()->IsKeyDown(DIK_LEFT))
							simon->Left();
						return;
					}

				}
				else // đã ở trên cầu thang
				{
					if (simon->isProcessingOnStair == 0 || simon->isProcessingOnStair == 3) // kết thúc xử lí trước đó
					{
						simon->isWalking = true;
						simon->isProcessingOnStair = 1;
						simon->trendY = 1;// hướng đi xuống
						simon->SetTrend(simon->trendStair*-1);// hướng của simon khi đi xuóng là ngược của cầu thang
						simon->SetSpeed(simon->GetTrend()* SIMON_SPEED_ONSTAIR, SIMON_SPEED_ONSTAIR);
					}

				}
			}
			else
			{
				simon->Stop();
			}
		} 

	}
	 





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

void Scene_2::OnKeyDown(int KeyCode)
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
 		DebugOut(L"[MOUSE POSITION] %d %d \n", p.x + (int)camera->GetXCam(), p.y + (int)camera->GetYCam());

		
	}


	if (KeyCode == DIK_3) // set vi tri simon 1275 
	{
		DebugOut(L"[SET POSITION SIMON] x = 1275 \n");
		simon->SetPosition(1275.0f, 0);
		simon->isAttacking = 0;
		simon->isWalking = 0;
		simon->isOnStair = 0;
		simon->isProcessingOnStair = 0;
	}

	if (KeyCode == DIK_4)  
	{
		DebugOut(L"[SET POSITION SIMON] x = .... \n");
		simon->SetPosition(3100.0f, 0);
	}


	if (KeyCode == DIK_R)
	{
		DebugOut(L"[RESET GRID]");
		SAFE_DELETE(gridGame);
		gridGame = new Grid();
		gridGame->ReadFileToGrid("Resources/map/Obj_2.txt"); // load lai
	}


	if (KeyCode == DIK_P) // tesst autogo 
	{
		simon->SetAutoGoX(simon->GetTrend(),-1,  200, SIMON_WALKING_SPEED);
	}


	if (KeyCode == DIK_G) // add ghost 
	{
		listEnemy.push_back(new Ghost(200, 200, 1));
	}


	if (simon->isAutoGoX == true) // đang chế độ tự đi thì ko xét phím
		return;









	if (KeyCode == DIK_X && simon->isProcessingOnStair == 0) // không phải đang xử lí việc đi trên thang thì đc đánh
	{
		//DebugOut(L"[SIMON] X = %f , Y = %f \n", simon->x + 10, simon->y);

		if (simon->isAttacking == false)
			sound->Play(eSound::soundWhip);

		simon->Attack(simon->_weaponMain);

	}


	if (KeyCode == DIK_Z)
	{
		if (simon->_weaponSub != NULL && simon->_weaponSub->GetFinish() == true && simon->GetHeartCollect() > 0)
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
			float vx, vy;
			simon->GetSpeed(vx, vy);
			simon->SetSpeed(SIMON_WALKING_SPEED * simon->GetTrend(), vy - SIMON_VJUMP);
			simon->isJumping = 1;
			simon->isWalking = 1;
		}
		else
		{ 
			simon->Jump();
		}



	}

}

void Scene_2::OnKeyUp(int KeyCode)
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


void Scene_2::LoadResources()
{
	TextureManager * _textureManager = TextureManager::GetInstance(); // Đã gọi load resource
	sound = Sound::GetInstance();

	if (simon==NULL)
		simon = new Simon();

	if (_gameTime == NULL)
		_gameTime = new GameTime();
	  
	TileMap = new Map();
	TileMap->LoadMap(eID::MAP2);

	camera = new Camera(Window_Width, Window_Height);
	camera->SetPosition(0, 0);


	board = new Board(0, 0);

	simon->SetPosition(SIMON_POSITION_DEFAULT);
	simon->SetPositionBackup(SIMON_POSITION_DEFAULT);

	gridGame = new Grid();
	gridGame->ReadFileToGrid("Resources/map/Obj_2.txt"); // đọc các object từ file vào Grid



	listItem.clear();
	listEffect.clear();
	listEnemy.clear();
	 
	// bật nhạc game
	if (sound->isPlaying(eSound::musicState1) == false)
		sound->Play(eSound::musicState1, true);

	CountEnemyGhost = 0;
	TimeCreateGhost = 0;
}

void Scene_2::Update(DWORD dt)
{

#pragma region Process_Freeze
	if (simon->GetFreeze() == true)
	{
		simon->UpdateFreeze(dt);
		if (simon->GetFreeze() == true)
			return;
	}
#pragma endregion

#pragma region Process_Gametime
	if (_gameTime->GetTime() >= GAME_TIME_SCENE2) // hết thời gian
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
		_gameTime->Update();



	if (GAME_TIME_SCENE2 - _gameTime->GetTime() <= 30) // đúng còn lại 30 giây thì bật sound loop
	{
		if (_gameTime->CheckIsJustChanged() == true) // Kiểm tra _time vừa thay đổi thì mới play nhạc. Nếu chỉ kt <=30s thì cứ mỗi deltatime nó sẽ Play nhạc -> thừa, ko đều
		{
			sound->Play(eSound::soundStopTimer);
		}
	}
#pragma endregion


	 
	gridGame->GetListObject(listObj, camera); // lấy hết các object "còn Alive" trong vùng camera;

	simon->Update(dt, &listObj);

	camera->SetPosition(simon->GetX() - Window_Width / 2 + 30, camera->GetYCam()); // cho camera chạy theo simon
	camera->Update();

#pragma region Process_Region_Create_Enemy_Ghost
 
//	DebugOut(L"now = %d - listenemy = %d\n", CountEnemyGhost, listEnemy.size());
	DWORD now = GetTickCount();

#pragma region Vùng 1
	if (simon->GetX() > 0 && simon->GetX() < 825)
	{
		if (now - TimeCreateGhost >= TIME_DISTANCE_CREATE_GHOST)
		{
			if (CountEnemyGhost < 3)
			{
				if (simon->GetVx() > 0) // vx>0 đang chạy về bên phải
				{
					// cho ghost chạy từ bên phải qua
					listEnemy.push_back(new Ghost(camera->GetXCam() + camera->GetWidth(), 326, -1));// 34 framewidth của ghost
				}
				else
					if (simon->GetVx() < 0) // vx>0 đang chạy về bên trái
					{
						// cho ghost chạy từ bên trái qua 
						listEnemy.push_back(new Ghost(camera->GetXCam() - 34, 326, 1));
					}
					else // đứng yên thì cứ random
					{
						int random = rand() % 2;
						if (random == 0) // đi từ bên trái
						{
							listEnemy.push_back(new Ghost(camera->GetXCam() - 34, 326, 1));
						}
						else // đi từ bên phải
						{
							listEnemy.push_back(new Ghost(camera->GetXCam() + camera->GetWidth(), 326, -1));
						}
					}
				 
				CountEnemyGhost++;
				TimeCreateGhost = now; // set lại thời điểm đã tạo ghost
			}
		}
	}
#pragma endregion

	 
#pragma endregion

	
#pragma region Process_Update_Object
	for (UINT i = 0; i < listObj.size(); i++)
		listObj[i]->Update(dt, &listObj);  // đã kiểm tra "Alive" lúc lấy từ lưới ra

	for (UINT i = 0; i < listItem.size(); i++)
		if (listItem[i]->GetFinish() == false)
			listItem[i]->Update(dt, &listObj); // trong các hàm update chỉ kiểm tra va chạm với đất

	for (UINT i = 0; i < listEffect.size(); i++)
		if (listEffect[i]->GetFinish() == false)
			listEffect[i]->Update(dt);

	for (UINT i = 0; i < listEnemy.size(); i++)
	{
		GameObject * enemy = dynamic_cast<GameObject *>(listEnemy[i]);
		if (enemy->GetHealth() > 0) // còn máu
		{
			if (camera->checkObjectInCamera(
				enemy->GetX(),
				enemy->GetY(),
				enemy->GetWidth(),
				enemy->GetHeight()) == false)  // vượt khỏi cam
			{
				enemy->SetHealth(0); // ra khỏi cam thì coi như chết
				if (dynamic_cast<Ghost*>(enemy) != NULL) // object này là ghost
				{
					CountEnemyGhost--; // giảm số lượng ghost hiện tại
				}
			}
			else
				enemy->Update(dt);
		}
	}
		
			
#pragma endregion



	CheckCollision();
}


void Scene_2::Render()
{

	TileMap->DrawMap(camera);


	for (UINT i = 0; i < listObj.size(); i++)
		listObj[i]->Render(camera);

	for (UINT i = 0; i < listItem.size(); i++)
		if (listItem[i]->GetFinish() == false)
			listItem[i]->Render(camera);

	for (UINT i = 0; i < listEffect.size(); i++)
		if (listEffect[i]->GetFinish() == false)
			listEffect[i]->Render(camera);

	for (UINT i = 0; i < listEnemy.size(); i++)
			listEnemy[i]->Render(camera);


	simon->Render(camera);

	board->Render(camera, simon, 1, simon->_weaponSub, GAME_TIME_SCENE2 - _gameTime->GetTime());



}

void Scene_2::ResetResource()
{
	SAFE_DELETE(gridGame);
	gridGame = new Grid();
	gridGame->ReadFileToGrid("Resources/map/Obj_2.txt"); // đọc lại các object từ list

	listItem.clear();
	listEffect.clear();
	
	CountEnemyGhost = 0;
	TimeCreateGhost = 0;

	_gameTime->SetTime(0); // đếm lại từ 0
	sound->Stop(eSound::musicState1); // tắt nhạc nền
	sound->Play(eSound::musicState1, true); // mở lại nhạc nền
}

void Scene_2::CheckCollision()
{
	CheckCollisionWeapon(listObj); // kt va chạm vũ khí với các object nền

	CheckCollisionSimonWithItem(); 
	CheckCollisionSimonWithObjectHidden();

	CheckCollisionWithEnemy(); // kt vũ khí cới enemy và simon với enemy

}

void Scene_2::CheckCollisionWeapon(vector<Object*> listObj)
{
	// main weapon
	if (simon->_weaponMain->GetFinish() == false) // Vũ khí đang hoạt động
	{
		for (UINT i = 0; i < listObj.size(); i++) // đã kt object còn sống hay k trong hàm va chạm của vũ khí
			if (simon->_weaponMain->isCollision(listObj[i]) == true) // nếu có va chạm thì kt kiểu
			{
				bool RunEffectHit = false;

				switch (listObj[i]->GetType())
				{
				case eID::CANDLE:
				{
					GameObject *gameObj = dynamic_cast<GameObject*>(listObj[i]);
					gameObj->SubHealth(1);
					listItem.push_back(GetNewItem(gameObj->GetId(), gameObj->GetType(), gameObj->GetX() + 5, gameObj->GetY()));
					RunEffectHit = true;
					break;
				}

				case eID::GHOST:
				{
					GameObject *gameObj = dynamic_cast<GameObject*>(listObj[i]);
					gameObj->SubHealth(1);
					
					if (rand() % 2 == 1) // tỉ lệ 50%
					{
						listItem.push_back(GetNewItem(gameObj->GetId(), gameObj->GetType(), gameObj->GetX() + 5, gameObj->GetY()));
					}
					
					RunEffectHit = true;
					CountEnemyGhost--; // giảm số lượng Ghost đang hoạt động
					break;
				}

				default:
					break;
				}



				if (RunEffectHit)
				{
					listEffect.push_back(new Hit((int)listObj[i]->GetX() + 10, (int)listObj[i]->GetY() + 14)); // hiệu ứng hit
					sound->Play(eSound::soundHit);
				}

			}
	}


	// subweapon
	if (simon->_weaponSub != NULL && simon->_weaponSub->GetFinish() == false)
	{
		for (UINT i = 0; i < listObj.size(); i++)// đã kt object còn sống hay k trong hàm va chạm của vũ khí
			if (simon->_weaponSub->isCollision(listObj[i]) == true) // nếu có va chạm thì kt kiểu
			{
				bool RunEffectHit = false;

				switch (listObj[i]->GetType())
				{
				case eID::CANDLE:
				{
					GameObject *gameObj = dynamic_cast<GameObject*>(listObj[i]);
					gameObj->SubHealth(1);
					listItem.push_back(GetNewItem(gameObj->GetId(), gameObj->GetType(), gameObj->GetX() + 5, gameObj->GetY()));
					RunEffectHit = true;

					break;
				}

				case eID::GHOST:
				{
					GameObject *gameObj = dynamic_cast<GameObject*>(listObj[i]);
					gameObj->SubHealth(1);

					if (rand() % 2 == 1) // tỉ lệ 50%
					{
						listItem.push_back(GetNewItem(gameObj->GetId(), gameObj->GetType(), gameObj->GetX() + 5, gameObj->GetY()));
					}
					RunEffectHit = true;
					CountEnemyGhost--; // giảm số lượng Ghost đang hoạt động
					break;
				}

				default:
					break;
				}




				if (RunEffectHit)
				{
					listEffect.push_back(new Hit((int)listObj[i]->GetX() + 10, (int)listObj[i]->GetY() + 14)); // hiệu ứng hit
					sound->Play(eSound::soundHit);
					simon->_weaponSub->SetFinish(true); // hủy cây kiếm
				}
			}
	}



}

void Scene_2::CheckCollisionSimonWithItem()
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
					sound->Play(eSound::soundCollectItem);
					break;
				}

				case eID::SMALLHEART:
				{
					simon->SetHeartCollect(simon->GetHeartCollect() + 1);
					listItem[i]->SetFinish(true);
					sound->Play(eSound::soundCollectItem);
					break;
				}


				case eID::UPGRADEMORNINGSTAR:
				{
					MorningStar * objMorningStar = dynamic_cast<MorningStar*>(simon->_weaponMain);
					objMorningStar->UpgradeLevel(); // Nâng cấp vũ khí roi
					listItem[i]->SetFinish(true);
					simon->SetFreeze(true); // bật trạng thái đóng băng
					sound->Play(eSound::soundCollectWeapon);
					break;
				} 
				case eID::ITEMDAGGER:
				{
					SAFE_DELETE(simon->_weaponSub);
					simon->_weaponSub = new Dagger();
					listItem[i]->SetFinish(true);
					sound->Play(eSound::soundCollectWeapon);
					break;
				}

				case eID::MONNEY:
				{
					listItem[i]->SetFinish(true);
					sound->Play(eSound::soundCollectItem);
					 
					break;
				}


				default:
					DebugOut(L"[CheckCollisionSimonWithItem] Khong nhan dang duoc loai Item!\n");
					break;
				}



			}
		}





}

void Scene_2::CheckCollisionSimonWithObjectHidden()
{
	for (UINT i = 0; i < listObj.size(); i++)
	{
		if (listObj[i]->GetType() == eID::OBJECT_HIDDEN)
		{
			GameObject * gameObject = dynamic_cast<GameObject*>(listObj[i]);
			if (gameObject->GetHealth() > 0)
			{
				LPCOLLISIONEVENT e = simon->SweptAABBEx(listObj[i]);
				if (0 < e->t && e->t <= 1) // có va chạm xảy ra
				{
					//switch (gameObject->GetId())
					//{
					//case 7: // đụng trúng cửa
					//{


					//	break;
					//}
					// 
					//}


					gameObject->SubHealth(1);

				}
			}
		}
	}
}

void Scene_2::CheckCollisionWithEnemy()
{
	CheckCollisionWeapon(listEnemy);
}




Item * Scene_2::GetNewItem(int Id, eID Type, float X, float Y)
{
	if (Type == eID::CANDLE)
	{
		return new SmallHeart(X, Y);
	} 


	if (Type == eID::GHOST)
	{
		int random = rand() % 10;
		switch (random)
		{
		case 0:
			return	new LargeHeart(X, Y);
			break;
		case 1:
			return	new SmallHeart(X, Y);
			break;
		case 2:
			return new ItemDagger(X, Y);
			break;
		case 3:
			return new Monney(X, Y);
			break;
		case 4:
			return new UpgradeMorningStar(X, Y);
			break;
		default: // 50% còn lại là SmallHeart
			return new SmallHeart(X, Y);
			break;
		} 
	}

	return new LargeHeart(X, Y);
}