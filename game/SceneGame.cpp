#include "SceneGame.h"
 
SceneGame::SceneGame()
{ 
	LoadResources();

}

SceneGame::~SceneGame()
{
	SAFE_DELETE(TileMap);
	SAFE_DELETE(board);
	SAFE_DELETE(gridGame);
}

void SceneGame::KeyState(BYTE * state)
{ 

	if (simon->GetFreeze() == true) // Đang bóng băng thì không quan tâm phím
	{
		return;
	}

	if (simon->GetIsDeadth() || isWaitResetGame || isGameOver)
	{
		return;
	}

	if (simon->GetIsAutoGoX() == true) // đang chế độ tự đi thì ko xét phím
		return;

	if (camera->GetIsAutoGoX()) // camera đang chế độ tự đi thì ko xét phím
		return;




	if (simon->isHurting)
		return;

	if (Game::GetInstance()->IsKeyDown(DIK_UP) && Game::GetInstance()->IsKeyDown(DIK_A) && simon->isProcessingOnStair==0 && !simon->isAttacking)
	{
		simon->Attack(simon->GetTypeWeaponCollect()); // attack với vũ khí phụ đang nhặt
	}
	else
		if (!simon->isJumping)
		{
			if (Game::GetInstance()->IsKeyDown(DIK_UP) && simon->isAttacking == false)
			{
				if (!simon->isOnStair) // chưa trên thang
				{
					for (UINT i = 0; i < listObj.size(); i++)
						if (listObj[i]->GetType() == eType::STAIR_BOTTOM)
						{
							if (simon->isCollisionAxisYWithBrick && simon->isCollitionObjectWithObject(listObj[i])) // nếu va chạm với trục y brick và STAIR BOTOM
							{
								GameObject* gameobj = dynamic_cast<GameObject*>(listObj[i]);
								simon->directionStair = gameobj->GetDirection(); // lưu hướng của cầu thang đang đi vào simon
								simon->directionY = -1;// hướng đi lên
								simon->SetDirection(simon->directionStair);// hướng của simon khi đi lên là hướng của cầu thang

								simon->isOnStair = true; // set trạng thái đang trên cầu thang
								simon->DoCaoDiDuoc = 0;

								if (simon->GetX() < gameobj->GetX())
								{
									simon->SetAutoGoX(1, gameobj->GetDirection(), gameobj->GetX() - simon->GetX(), SIMON_WALKING_SPEED);
									// hướng sau khi autogo phải là hướng của cầu thang:  gameobj->GetDirection()
								}
								else
									simon->SetAutoGoX(-1, gameobj->GetDirection(), simon->GetX() - gameobj->GetX(), SIMON_WALKING_SPEED);
								//	DebugOut(L"bat dau len cau thang!\n"); 
								return;
							}
						}
				}
				else // nếu đã trên cầu thang
				{
					//	DebugOut(L"Da o tren cau thang!\n");

					if (simon->isProcessingOnStair == 0 || simon->isProcessingOnStair == 3) // kết thúc xử lí trước đó
					{
						simon->isWalking = true;
						simon->isProcessingOnStair = 1;
						simon->directionY = -1;// hướng đi lên
						simon->SetDirection(simon->directionStair);// hướng của simon khi đi lên là hướng của cầu thang
						simon->SetSpeed(simon->GetDirection()* SIMON_SPEED_ONSTAIR, -1 * SIMON_SPEED_ONSTAIR);

						float vvx, vvy;
						simon->GetSpeed(vvx, vvy);
						//DebugOut(L"vy = %f\n", vvy);
					}


				}
			}
			else
			{
				if (Game::GetInstance()->IsKeyDown(DIK_DOWN) && simon->isAttacking == false) // ngược lại nếu nhấn nút xuống
				{
					if (!simon->isOnStair) // chưa trên cầu thang
					{
						int CountCollisionTop = 0;
						for (UINT i = 0; i < listObj.size(); i++)
							if (listObj[i]->GetType() == eType::STAIR_TOP)
							{
								if (simon->isCollitionObjectWithObject(listObj[i])
									//&& simon->isCheckCollisionAxisY_WithBrickSweptAABB(&listObj)
									&&
									simon->isCollisionAxisYWithBrick
									) // nếu va chạm với STAIR TOP
								{
									GameObject* gameobj = dynamic_cast<GameObject*>(listObj[i]);
									simon->directionStair = gameobj->GetDirection(); // lưu hướng của cầu thang đang đi vào simon
									simon->directionY = 1;// hướng đi xuống
									simon->SetDirection(simon->directionStair);// hướng của simon khi đi xuống là hướng của cầu thang

									simon->isOnStair = true; // set trạng thái đang trên cầu thang
									simon->DoCaoDiDuoc = 0;


									if (simon->GetX() < gameobj->GetX())
									{
										simon->SetAutoGoX(1, -gameobj->GetDirection(), gameobj->GetX() - simon->GetX(), SIMON_WALKING_SPEED);
										// hướng sau khi autogo phải là hướng của cầu thang:  gameobj->GetDirection()
									}
									else
										simon->SetAutoGoX(-1, -gameobj->GetDirection(), simon->GetX() - gameobj->GetX(), SIMON_WALKING_SPEED);



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
							simon->directionY = 1;// hướng đi xuống
							simon->SetDirection(simon->directionStair*-1);// hướng của simon khi đi xuóng là ngược của cầu thang
							simon->SetSpeed(simon->GetDirection()* SIMON_SPEED_ONSTAIR, SIMON_SPEED_ONSTAIR);
						}

					}
				}
				else
				{
					simon->Stop();
				}
			}

		}


	if (simon->isJumping && simon->isWalking)
	{
		return;
	}


	if (simon->isOnStair) // nếu đang trên thang thì không xét loại đi trái phải bt
		return;

	if (simon->isAttacking) // đang attack
	{
		float vx, vy;
		simon->GetSpeed(vx, vy);
		simon->SetSpeed(0, vy);
		//DebugOut(L"DIK_RIGHT & attack \n");

		return;
	}

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

void SceneGame::OnKeyDown(int KeyCode)
{
	if (KeyCode == DIK_R) // render bbox
	{
		if (isDebug_RenderBBox == 0)
			isDebug_RenderBBox = 1;
		else
			isDebug_RenderBBox = 0;
	}

	if (simon->GetFreeze() == true) // Đang bóng băng thì không quan tâm phím
	{
		return;
	}

	if (isGameOver)
	{
		switch (KeyCode)
		{
		case DIK_UP:
		{
			GameOverSelect = GAMEOVER_SELECT_CONTINUE;
			break;
		}
		case DIK_DOWN:
		{
			GameOverSelect = GAMEOVER_SELECT_END;
			break;
		}
		case DIK_RETURN:
		{
			if (GameOverSelect == GAMEOVER_SELECT_CONTINUE)
			{
				InitGame(); 
				isGameOver = false; 
			}
			else
				if (GameOverSelect == GAMEOVER_SELECT_END)
				{
					DestroyWindow(Game::GetInstance()->GetWindowHandle()); // thoát
				}
			break;
		}
		}

		return;
	}

	if (simon->GetIsDeadth() || isWaitResetGame)
	{
		return;
	}
 
	if (KeyCode == DIK_ESCAPE)
		DestroyWindow(Game::GetInstance()->GetWindowHandle()); // thoát

#pragma region Keydown Debug
	 
	if (KeyCode == DIK_1) // vị trí simon
	{
		DebugOut(L"[SIMON] X = %f , Y = %f \n", simon->GetX(), simon->GetY());
	}
	 
	if (KeyCode == DIK_2) // lấy tọa độ world của chuột 
	{
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(Game::GetInstance()->GetWindowHandle(), &p);
		DebugOut(L"[MOUSE POSITION] %d %d \n", p.x + (int)camera->GetXCam(), p.y + (int)camera->GetYCam());
	}


	if (KeyCode == DIK_3) // set vi tri simon   
	{
		DebugOut(L"[SET POSITION SIMON] x = 1140.0f \n");
		simon->SetPosition(1140.0f, 0);
		simon->isAttacking = 0;
		simon->isWalking = 0;
		simon->isOnStair = 0;
		simon->isProcessingOnStair = 0;
	}

	if (KeyCode == DIK_4)
	{
		DebugOut(L"[SET POSITION SIMON] x = .... \n");
		simon->SetPosition(2787.0f, 0);
		//	simon->isOnStair = false;
	}

	if (KeyCode == DIK_5)
	{
		DebugOut(L"[SET POSITION SIMON] x = .... \n");
		simon->SetPosition(2060.0f, 0);
	}


	if (KeyCode == DIK_8) // đứng xuoosg hồ nước
	{
		DebugOut(L"[SET POSITION SIMON] x = .... \n");
		simon->SetPosition(3084.0f, 310.0f);


		camera->SetBoundary(CAMERA_BOUNDARY_LAKE_LEFT, CAMERA_BOUNDARY_LAKE_RIGHT);

		simon->Stop(); // cho simon dừng, tránh trường hợp không vào được trạng thái stop trong KeyState()
		isProcessingGoThroughTheDoor1 = true; // bật trạng thái xử lí qua cửa 
		isDoneSimonGoThroughTheDoor1 = true;

		simon->SetPositionBackup(simon->GetX(), 0); // backup lại vị trí sau khi qua màn 
		TimeCreateBat = GetTickCount();
		TimeWaitCreateBat = 2000;
		isAllowCreateBat = true;
		StateCurrent = 2;// set hiển thị đang ở state2
		camera->SetPositionBackup(camera->GetXCam(), camera->GetYCam());




		camera->SetPosition(camera->GetXCam(), CAMERA_POSITION_Y_LAKE);
		simon->SetPosition(3150, 405);
		isAllowCreateBat = false;  // không cho tạo Bat
		isAllowCreateFishmen = true;


	}


	if (KeyCode == DIK_7)
	{
		DebugOut(L"[SET POSITION SIMON] x = .... \n");
		simon->SetPosition(4000.0f, 500.0f);
	}


	if (KeyCode == DIK_6)
	{
		DebugOut(L"[SET POSITION SIMON] x = .... \n");
		simon->SetPosition(3940, 100);
		camera->SetPosition(camera->GetXCam(), 0);
		isAllowCreateFishmen = false;
	}

	if (KeyCode == DIK_Y) // run boss
	{
		boss->Start();
	}

	if (KeyCode == DIK_0) // boss
	{
		simon->SetPosition(5328.0f, 240.0f);

		camera->SetBoundary(CAMERA_BOUNDARY_BOSS_RIGHT, CAMERA_BOUNDARY_BOSS_RIGHT);

		simon->Stop(); // cho simon dừng, tránh trường hợp không vào được trạng thái stop trong KeyState()

		camera->SetPosition(camera->GetXCam(), 0);

		boss = new PhantomBat(simon, camera, &listWeaponOfEnemy);
	}
 

	if (KeyCode == DIK_9) // đứng ngay cầu thang gần xuoosg hồ nước
	{
		DebugOut(L"[SET POSITION SIMON] x = .... \n");
		simon->SetPosition(3084.0f, 310.0f);

		camera->SetBoundary(3073, camera->GetBoundaryRight() + 1023);// mở biên phải rộng ra thêm để chạy AutoGo
		//camera->SetAutoGoX(abs(GATE1_POSITION_CAM_BEFORE_GO - camera->GetXCam()), SIMON_WALKING_SPEED);
		simon->Stop(); // cho simon dừng, tránh trường hợp không vào được trạng thái stop trong KeyState()
		isProcessingGoThroughTheDoor1 = true; // bật trạng thái xử lí qua cửa
		isDoneSimonGoThroughTheDoor1 = false;
		isDoneSimonGoThroughTheDoor1 = true;
		simon->SetPositionBackup(simon->GetX(), 0); // backup lại vị trí sau khi qua màn 
		TimeCreateBat = GetTickCount();
		TimeWaitCreateBat = 2000;
		isAllowCreateBat = true;
		StateCurrent = 2;// set hiển thị đang ở state2
		camera->SetPositionBackup(camera->GetXCam(), camera->GetYCam());
	}




	if (KeyCode == DIK_U)
	{
		if (isDebug_Untouchable == 1)
			isDebug_Untouchable = 0;
		else
			isDebug_Untouchable = 1;
	}

	if (KeyCode == DIK_R)
	{
		DebugOut(L"[RESET GRID]");
		gridGame->ReloadGrid();
	}
 
  
	if (KeyCode == DIK_F) // create hollywater
	{
		simon->SetHealth(SIMON_DEFAULT_HEALTH);
		simon->SetLives(99);
		simon->SetHeartCollect(99);
		gameTime->SetTime(0);
	}


#pragma endregion

	if (simon->GetIsAutoGoX() == true) // đang chế độ tự đi thì ko xét phím
		return;

	if (camera->GetIsAutoGoX()) // camera đang chế độ tự đi thì ko xét phím
		return;


	if (simon->isHurting)
		return;


	//if (KeyCode == DIK_A && Game::GetInstance()->IsKeyDown(DIK_UP) && simon->isProcessingOnStair == 0)
	//{
	//	simon->Attack(simon->GetTypeWeaponCollect()); // attack với vũ khí phụ đang nhặt
	//}
	//else

	if (!(Game::GetInstance()->IsKeyDown(DIK_UP) && Game::GetInstance()->IsKeyDown(DIK_A) /*&& simon->isProcessingOnStair == 0*/ && simon->isAttacking==true))
		if (KeyCode == DIK_A && simon->isProcessingOnStair == 0) // không phải đang xử lí việc đi trên thang thì đc đánh
		{
			simon->Attack(eType::MORNINGSTAR);
		}
	 

	if (simon->isJumping && simon->isWalking)
	{
		return;
	}


	if (KeyCode == DIK_S && simon->isOnStair == false)
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

void SceneGame::OnKeyUp(int KeyCode)
{
	if (simon->GetFreeze() == true) // Đang bóng băng thì không quan tâm phím
	{
		return;
	}

	if (simon->GetIsDeadth() || isWaitResetGame || isGameOver)
	{
		return;
	}


}

void SceneGame::LoadResources()
{
	TextureManager * _textureManager = TextureManager::GetInstance();
	sound = Sound::GetInstance();

	gameTime = new GameTime();

	TileMap = new Map();
	gridGame = new Grid();

	camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);
	simon = new Simon(camera);
	board = new Board(BOARD_DEFAULT_POSITION_X, BOARD_DEFAULT_POSITION_Y);

	_spriteLagerHeart = new GSprite(TextureManager::GetInstance()->GetTexture(eType::LARGEHEART), 100);
	 
	InitGame();
}

void SceneGame::InitGame()
{
	LoadMap(eType::MAP1);
	simon->Init();

	//ResetResource();
	

	gameTime->SetTime(0); // đếm lại từ 0
	
	ReplayMusicGame();


}

void SceneGame::ResetResource()
{ 
	gridGame->ReloadGrid(); // nạp lại lưới

	listItem.clear();
	listEffect.clear();
	listEnemy.clear();
	listWeaponOfEnemy.clear();

	CountEnemyGhost = 0;
	TimeCreateGhost = 0;
	isWaitProcessCreateGhost = false; // lúc đầu thì không cần chờ

	isAllowRenewPanther = true;
	CountEnemyPanther = 0;

	isAllowCreateFishmen = false;
	TimeCreateFishmen = 0;
	TimeWaitCreateFishmen = 0;
	CountEnemyFishmen = 0;

	TimeCreateBat = 0;
	TimeWaitCreateBat = 0;
	isAllowCreateBat = 0;
	 
	camera->SetAllowFollowSimon(true);

	isProcessingGoThroughTheDoor1 = false; // ban đầu chưa cần xử lí qua cửa
	isDoneSimonGoThroughTheDoor1 = false;

	isProcessingGoThroughTheDoor2 = false; // ban đầu chưa cần xử lí qua cửa
	isDoneSimonGoThroughTheDoor2 = false;

	if (boss != NULL)
	{
		boss->ResetResource();
	}

	isUseInvisibilityPotion = false;
	isUseCross = false;

	/* Set Chờ hiển thị màn đen */
	isWaitResetGame = true;
	TimeWaitedResetGame = 0;

	/*init gameover*/
	isGameOver = false;
	GameOverSelect = GAMEOVER_SELECT_CONTINUE;
}

void SceneGame::Update(DWORD dt)
{
	if (isGameOver)
		return;

#pragma region process debug

	if (isDebug_Untouchable == 1)
		simon->StartUntouchable();

#pragma endregion

#pragma region xử lí vẽ màn đen trước khi bắt đầu game
	if (isWaitResetGame)
	{
		TimeWaitedResetGame += dt;
		if (TimeWaitedResetGame >= TIME_LIMIT_WAIT_RESET_GAME)
		{
			isWaitResetGame = false;
		}
		else
			return;
	}
#pragma endregion

#pragma region Process_Freeze
	if (simon->GetFreeze() == true)
	{
		simon->UpdateFreeze(dt);
		if (simon->GetFreeze() == true)
			return;
	}
#pragma endregion

	ProcessClearState3(dt); // xử lí sau khi diệt xong boss
	ProcessInvisibilityPotion(dt);
	ProcessCross(dt);


	if (!isAllowProcessClearState3)
	{

#pragma region Process_Gametime_OR_Health
		if (gameTime->GetTime() >= GAME_TIME_MAX || simon->GetHealth() <= 0) // hết thời gian hoặc hết máu
		{
			if (simon->GetIsDeadth())
			{
				simon->TimeWaitedAfterDeath += dt;
				if (simon->TimeWaitedAfterDeath >= 1500)
				{ 
						bool result = simon->LoseLife(); // đã khôi phục x,y

						if (result == true) // còn mạng để chơi tiếp, giảm mạng reset máu xong
						{
							camera->RestorePosition(); // khôi phục vị trí camera;
							camera->RestoreBoundary(); // khôi phục biên camera

							gameTime->SetTime(0);
							ReplayMusicGame();

							ResetResource(); // reset lại game
						}
						else
						{
							isGameOver = true;
						} 
					return;
				}
			}
			else // chưa chết mà hết máu hoặc time thì set trạng thái isDeadth
			{
				simon->SetDeadth();
			}

		}
		else
		{
			if (isAllowProcessClearState3 == false) // đang xử lí ClearState thì không đếm time
			{
				gameTime->Update(dt);
			}
		}




		if (GAME_TIME_MAX - gameTime->GetTime() <= 30) // đúng còn lại 30 giây thì bật sound loop
		{
			if (gameTime->CheckIsJustChanged() == true) // Kiểm tra _time vừa thay đổi thì mới play nhạc. Nếu chỉ kt <=30s thì cứ mỗi deltatime nó sẽ Play nhạc -> thừa, ko đều
			{
				sound->Play(eSound::soundStopTimer);
			}
		}
#pragma endregion

	}


#pragma region Process Gate 1

	if (isProcessingGoThroughTheDoor1) // simon chạm cửa thì bắt đầu xử lí
	{
		if (isDoneSimonGoThroughTheDoor1 == false) // simon chưa hoàn thành việc qua cửa
		{
			if (camera->GetXCam() >= GATE1_POSITION_CAM_BEFORE_GO) // camera đã AutoGo xong đến vị trí 2825.0f
			{
				simon->SetAutoGoX(1, 1, abs(GATE1_POSITION_CAM_AFTER_GO + DISTANCE_AUTO_WALK_AFTER_GATE - simon->GetX()), SIMON_WALKING_SPEED); // bắt đầu cho simon di chuyển tự động đến vị trí tiếp theo
			}
		}
		else
		{
			if (camera->GetXCam() >= GATE1_POSITION_CAM_AFTER_GO)
			{
				camera->SetBoundary(GATE1_POSITION_CAM_AFTER_GO, camera->GetBoundaryRight());

				camera->SetBoundaryBackup(camera->GetBoundaryLeft(), camera->GetBoundaryRight());

				camera->SetAllowFollowSimon(true);
				isProcessingGoThroughTheDoor1 = false; // xong việc xử lí qua cửa 1
				camera->StopAutoGoX(); // dừng việc tự di chuyển
			}
		}
	}

#pragma endregion

#pragma region Process Gate 2

	if (isProcessingGoThroughTheDoor2) // simon chạm cửa thì bắt đầu xử lí
	{
		if (isDoneSimonGoThroughTheDoor2 == false) // simon chưa hoàn thành việc qua cửa
		{
			if (camera->GetXCam() >= GATE2_POSITION_CAM_BEFORE_GO)
			{
				simon->SetAutoGoX(1, 1, abs(GATE2_POSITION_CAM_AFTER_GO + DISTANCE_AUTO_WALK_AFTER_GATE - simon->GetX()), SIMON_WALKING_SPEED); // bắt đầu cho simon di chuyển tự động đến vị trí tiếp theo
			}
		}
		else
		{
			if (camera->GetXCam() >= GATE2_POSITION_CAM_AFTER_GO)
			{
				camera->SetBoundary(GATE2_POSITION_CAM_AFTER_GO, camera->GetBoundaryRight());

				camera->SetBoundaryBackup(camera->GetBoundaryLeft(), camera->GetBoundaryRight());

				camera->SetAllowFollowSimon(true);
				isProcessingGoThroughTheDoor2 = false; // xong việc xử lí qua cửa 2
				camera->StopAutoGoX(); // dừng việc tự di chuyển
			}
		}
	}

#pragma endregion
	 


	gridGame->GetListObject(listObj, camera); // lấy hết các object "còn Alive" trong vùng camera;



 
	simon->Update(dt, &listObj);

	if (camera->AllowFollowSimon())
		camera->SetPosition(simon->GetX() - SCREEN_WIDTH / 2 + 30, camera->GetYCam()); // cho camera chạy theo simon

	camera->Update(dt);


	if (mapCurrent == eType::MAP2)
	{
#pragma region Process_Region_Create_Enemy_Ghost

		//	DebugOut(L"now = %d - listenemy = %d\n", CountEnemyGhost, listEnemy.size());
		DWORD now = GetTickCount();



		if (isWaitProcessCreateGhost == false) // nếu không phải chờ xử lí thì vào xử lí
		{
#pragma region Vùng 1 & Vùng 2
			if ((simon->GetX() >= -16.0f && simon->GetX() <= 825.0f) || (simon->GetX() > 2200 && simon->GetX() < 2775))
			{
				if (now - TimeCreateGhost >= ThoiGianChoGiua2GhostDuocTao)
				{
					if (CountEnemyGhost < 3)
					{
						if (simon->GetVx() > 0) // vx>0 đang chạy về bên phải
						{
							// cho ghost chạy từ bên phải qua
							listEnemy.push_back(new Ghost(camera->GetXCam() + camera->GetWidth(), 326 - 10, -1));// 34 framewidth của ghost
						}
						else
							if (simon->GetVx() < 0) // vx>0 đang chạy về bên trái
							{
								// cho ghost chạy từ bên trái qua 
								listEnemy.push_back(new Ghost(camera->GetXCam() - 34, 326 - 10, 1));
							}
							else // đứng yên thì cứ random
							{
								int random = rand() % 2;
								if (random == 0) // đi từ bên trái
								{
									listEnemy.push_back(new Ghost(camera->GetXCam() - 34, 326 - 10, 1));
								}
								else // đi từ bên phải
								{
									listEnemy.push_back(new Ghost(camera->GetXCam() + camera->GetWidth(), 326 - 10, -1));
								}
							}
						CountEnemyGhost++;
						if (CountEnemyGhost == 3)
						{
							isWaitProcessCreateGhost = true; // phải chờ đến khi cả 3 ghost bị giết
							isAllowCheckTimeWaitProcessCreateGhost = false;
						}
						TimeCreateGhost = now; // set lại thời điểm đã tạo ghost
					}
				}
			}
#pragma endregion

#pragma region Vùng 3
			if ((simon->GetX() >= GHOST_ZONE3_LEFT && simon->GetX() <= GHOST_ZONE3_RIGHT))
			{
				if (now - TimeCreateGhost >= ThoiGianChoGiua2GhostDuocTao)
				{
					if (CountEnemyGhost < 3)
					{

						int random = rand() % 2; // tỉ lệ 50%
						switch (random)
						{
						case 0: // ở trên
						{
							if (simon->GetX() <= GHOST_ZONE3_COLUMN1)
							{
								listEnemy.push_back(new Ghost(camera->GetXCam() + camera->GetWidth(), 185, -1));// bên phải chạy qua trái
								break;
							}
							else
								if (GHOST_ZONE3_COLUMN2 <= simon->GetX())
								{
									listEnemy.push_back(new Ghost(camera->GetXCam() - 34, 185, 1));// bên trái qua phải
									break;
								}
								else
								{
									// không break, để tự chạy tiếp tục vào case 1
								}
						}
						case 1: // ở dưới
						{
							if (simon->GetVx() > 0) // đang chạy về bên phải
								listEnemy.push_back(new Ghost(camera->GetXCam() + camera->GetWidth(), 330, -1));// bên phải chạy qua trái
							else
								if (simon->GetVx() < 0) // đang chạy bên trái 
									listEnemy.push_back(new Ghost(camera->GetXCam() - 34, 330, 1)); // đi từ trái qua phải
								else
								{
									if (rand() % 2 == 0)
										listEnemy.push_back(new Ghost(camera->GetXCam() + camera->GetWidth(), 330, -1));// bên phải chạy qua trái
									else
										listEnemy.push_back(new Ghost(camera->GetXCam() - 34, 330, 1)); // đi từ trái qua phải 
								}
							break;
						}

						}

						CountEnemyGhost++;
						if (CountEnemyGhost == 3)
						{
							isWaitProcessCreateGhost = true; // phải chờ đến khi cả 3 ghost bị giết
							isAllowCheckTimeWaitProcessCreateGhost = false;
						}
						TimeCreateGhost = now; // set lại thời điểm đã tạo ghost



					/*
					if (simon->GetVx() > 0) // vx>0 đang chạy về bên phải
					{
						// cho ghost chạy từ bên phải qua
						listEnemy.push_back(new Ghost(camera->GetXCam() + camera->GetWidth(), 326 - 10, -1));// 34 framewidth của ghost
					}
					else
						if (simon->GetVx() < 0) // vx>0 đang chạy về bên trái
						{
							// cho ghost chạy từ bên trái qua
							listEnemy.push_back(new Ghost(camera->GetXCam() - 34, 326 - 10, 1));
						}
						else // đứng yên thì cứ random
						{
							int random = rand() % 2;
							if (random == 0) // đi từ bên trái
							{
								listEnemy.push_back(new Ghost(camera->GetXCam() - 34, 326 - 10, 1));
							}
							else // đi từ bên phải
							{
								listEnemy.push_back(new Ghost(camera->GetXCam() + camera->GetWidth(), 326 - 10, -1));
							}
						}
					CountEnemyGhost++;
					if (CountEnemyGhost == 3)
					{
						isWaitProcessCreateGhost = true; // phải chờ đến khi cả 3 ghost bị giết
						isAllowCheckTimeWaitProcessCreateGhost = false;
					}
					TimeCreateGhost = now; // set lại thời điểm đã tạo ghost
					*/
					}
				}
			}
#pragma endregion

		}
		else
		{
			if (isAllowCheckTimeWaitProcessCreateGhost)
			{
				if (now - TimeWaitProcessCreateGhost >= ThoiGianChoDeXuLiTaoGhost) // đã chờ đủ
				{
					isWaitProcessCreateGhost = false; // không phải chờ nữa
				}
			}
		}




#pragma endregion

#pragma region Process_Region_Create_Panther
		if (REGION_CREATE_PANTHER_LEFT < simon->GetX() && simon->GetX() < REGION_CREATE_PANTHER_RIGHT)
		{
			if (isAllowRenewPanther)
			{
				if (CountEnemyPanther == 0) // không còn Panther nào sống thì mới dc tạo lại cả 3
				{
					int directionPanther = abs(REGION_CREATE_PANTHER_LEFT - simon->GetX()) < abs(REGION_CREATE_PANTHER_RIGHT - simon->GetX()) ? -1 : 1; // hướng mặt của Panther quay về hướng simon
					listEnemy.push_back(new Panther(1398.0f, 225.0f, directionPanther, directionPanther == -1 ? 20.0f : 9.0f, simon));
					listEnemy.push_back(new Panther(1783.0f, 160.0f, directionPanther, directionPanther == -1 ? 278.0f : 180.0f, simon));
					listEnemy.push_back(new Panther(1923.0f, 225.0f, directionPanther, directionPanther == -1 ? 68.0f : 66.0f, simon));
					CountEnemyPanther += 3;
				}
				isAllowRenewPanther = false;
			}
		}
		else
		{
			isAllowRenewPanther = true;
		}
#pragma endregion

#pragma region Create_Bat 
		if (isAllowCreateBat)
		{
			DWORD now = GetTickCount();
			if (now - TimeCreateBat >= TimeWaitCreateBat) // đủ thời gian chờ
			{
				TimeCreateBat = now; // đặt lại thời gian đã tạo bat
				if (simon->GetX() < CREATE_BAT_BOUNDARY_DIVISION_DIRECTION_X || (simon->GetX() > CREATE_BAT_BOUNDARY_DIVISION_DIRECTION_X && simon->GetY() > CREATE_BAT_BOUNDARY_DIVISION_DIRECTION_Y))
					listEnemy.push_back(new Bat(camera->GetXCam() + camera->GetWidth() - 10, simon->GetY() + 40, -1));
				else
					listEnemy.push_back(new Bat(camera->GetXCam() - 10, simon->GetY() + 40, 1));

				TimeWaitCreateBat = 4000 + (rand() % 3000);
			}
		}
#pragma endregion

#pragma region Create Fishmen


		if (isAllowCreateFishmen && CountEnemyFishmen < 2)
		{
			DWORD now = GetTickCount();
			if (now - TimeCreateFishmen >= TimeWaitCreateFishmen) // đủ thời gian chờ
			{
				TimeCreateFishmen = now; // đặt lại thời gian đã tạo

				float vtx = 0;

				if (FISHMEN_ZONE_1_LEFT < simon->GetX() && simon->GetX() <= FISHMEN_ZONE_1_RIGHT)
				{
					vtx = (rand() % 2) ? (FISHMEN_POS_3) : (FISHMEN_POS_4);
				}

				if (FISHMEN_ZONE_2_LEFT < simon->GetX() && simon->GetX() <= FISHMEN_ZONE_2_RIGHT)
				{
					vtx = (rand() % 2) ? (FISHMEN_POS_1) : ((rand() % 2) ? (FISHMEN_POS_3) : (FISHMEN_POS_4));
				}

				if (FISHMEN_ZONE_3_LEFT < simon->GetX() && simon->GetX() <= FISHMEN_ZONE_3_RIGHT)
				{
					vtx = (rand() % 2) ? (FISHMEN_POS_4) : (FISHMEN_POS_5);
				}

				if (FISHMEN_ZONE_4_LEFT < simon->GetX() && simon->GetX() <= FISHMEN_ZONE_4_RIGHT)
				{
					vtx = (rand() % 2) ? (FISHMEN_POS_3) : (FISHMEN_POS_5);
				}

				if (FISHMEN_ZONE_5_LEFT < simon->GetX() && simon->GetX() <= FISHMEN_ZONE_5_RIGHT)
				{
					vtx = (rand() % 2) ? (FISHMEN_POS_4) : (FISHMEN_POS_6);
				}

				if (FISHMEN_ZONE_6_LEFT < simon->GetX() && simon->GetX() <= FISHMEN_ZONE_6_RIGHT)
				{
					vtx = (rand() % 2) ? (FISHMEN_POS_5) : ((rand() % 2) ? (FISHMEN_POS_7) : (FISHMEN_POS_8));
				}

				if (FISHMEN_ZONE_7_LEFT < simon->GetX() && simon->GetX() <= FISHMEN_ZONE_7_RIGHT)
				{
					vtx = (rand() % 2) ? (FISHMEN_POS_6) : (FISHMEN_POS_8);
				}
				if (FISHMEN_ZONE_8_LEFT < simon->GetX() && simon->GetX() <= FISHMEN_ZONE_8_RIGHT)
				{
					vtx = (rand() % 2) ? (FISHMEN_POS_6) : (FISHMEN_POS_7);
				}
				int directionFishmen = vtx < simon->GetX() ? 1 : -1;


				float vty = FISHMEN_POS_Y;

				listEnemy.push_back(new Fishmen(vtx, vty, directionFishmen, simon, &listWeaponOfEnemy, camera));
				CountEnemyFishmen++;

				STEAM_ADD_EFFECT(listEffect, vtx, vty);

				sound->Play(eSound::soundSplashwater);
				TimeWaitCreateFishmen = 2000 + (rand() % 2000);
			}
		}

#pragma endregion
	}



#pragma region Process_Update_Object

	for (UINT i = 0; i < listObj.size(); i++)
		listObj[i]->Update(dt, &listObj);  // đã kiểm tra "Alive" lúc lấy từ lưới ra

	for (UINT i = 0; i < listItem.size(); i++)
		if (listItem[i]->GetFinish() == false)
			listItem[i]->Update(dt, &listObj); // trong các hàm update chỉ kiểm tra va chạm với đất

	for (UINT i = 0; i < listEffect.size(); i++)
		if (listEffect[i]->GetFinish() == false)
			listEffect[i]->Update(dt);

	if (!simon->IsUsingWeapon(eType::STOPWATCH)) // đang dùng stopwatch thì không update enemy
	{
		for (UINT i = 0; i < listEnemy.size(); i++)
		{
			GameObject * enemy = listEnemy[i];
			if (enemy->GetHealth() > 0) // còn máu
			{
				switch (enemy->GetType())
				{
				case eType::GHOST:
				{
					if (camera->CHECK_OBJECT_IN_CAMERA(enemy) == false)  // vượt khỏi cam
					{
						enemy->SetHealth(0); // ra khỏi cam thì coi như chết
						CountEnemyGhost--; // giảm số lượng ghost hiện tại
						if (CountEnemyGhost == 0)
						{
							TimeWaitProcessCreateGhost = GetTickCount(); // set thời điểm hiện tại
							isWaitProcessCreateGhost = true;
							isAllowCheckTimeWaitProcessCreateGhost = true;
						}
					}
					else
						enemy->Update(dt, &listObj);
					break;
				}

				case eType::PANTHER:
				{
					if (camera->CHECK_OBJECT_IN_CAMERA(enemy)) // nếu Panther nằm trong camera thì update
						// vì do Grid load object nền (Brick) dựa vào vùng camera, nên có nguy cơ khiến 1 số object Panther không xét được va chạm đất.
					{
						enemy->Update(dt, &listObj);
					}
					else // nằm ngoài camera
					{
						Panther * objPanther = dynamic_cast<Panther *>(enemy);
						if (objPanther->GetIsStart())// ngoài cam và đã được kích hoạt r
						{
							objPanther->SetHealth(0); // cho Panther chết
							CountEnemyPanther--;
						}
					}
					break;
				}


				case eType::BAT:
				{
					if (camera->CHECK_OBJECT_IN_CAMERA(enemy)) // nếu nằm trong camera thì update
					{
						enemy->Update(dt);
					}
					else
					{
						enemy->SetHealth(0); // ra khỏi cam coi như chết
					}

					break;
				}

				case eType::FISHMEN:
				{
					if (camera->CHECK_OBJECT_IN_CAMERA(enemy)) // nếu nằm trong camera thì update
					{
						enemy->Update(dt, &listObj);
					}
					else
					{
						enemy->SetHealth(0); // ra khỏi cam coi như chết
						CountEnemyFishmen--;
					}
					break;
				}

				default:
					break;
				}
			}
		}

		if (boss != NULL)
			boss->Update(dt, &listObj);
	}

	for (UINT i = 0; i < listWeaponOfEnemy.size(); i++)
	{
		if (listWeaponOfEnemy[i]->GetFinish() == false)
		{
			listWeaponOfEnemy[i]->Update(dt, &listObj);
		}
	}
#pragma endregion


	if (!simon->GetIsDeadth())
	{
		CheckCollision();
	}

}

void SceneGame::Render()
{
	if (isWaitResetGame) // màn đen trước khi bắt đầu game
		return; // thoát và ko vẽ gì

	if (!isGameOver)
	{
		TileMap->DrawMap(camera);

		for (UINT i = 0; i < listObj.size(); i++)
			listObj[i]->Render(camera);

		for (UINT i = 0; i < listItem.size(); i++)
			if (listItem[i]->GetFinish() == false)
				listItem[i]->Render(camera);



		for (UINT i = 0; i < listEnemy.size(); i++)
			listEnemy[i]->Render(camera);


		simon->Render(camera);


		for (UINT i = 0; i < listEffect.size(); i++)
			if (listEffect[i]->GetFinish() == false)
				listEffect[i]->Render(camera);

		if (boss != NULL)
			boss->Render(camera);


		for (UINT i = 0; i < listWeaponOfEnemy.size(); i++)
			listWeaponOfEnemy[i]->Render(camera);
	}
	else
	{
		Text.Draw(200, 200, "GAME OVER");
		Text.Draw(215, 250, "CONTINUE");
		Text.Draw(215, 280, "END");
		switch (GameOverSelect)
		{
		case GAMEOVER_SELECT_CONTINUE:
		{
			_spriteLagerHeart->Draw(175, 245);
			break;
		}
		case GAMEOVER_SELECT_END:
		{
			_spriteLagerHeart->Draw(175, 275);
			break;
		}
		}
	}

	board->Render(simon, StateCurrent, GAME_TIME_MAX - gameTime->GetTime(), boss);
}

void SceneGame::LoadMap(eType x)
{
	mapCurrent = x;

	switch (x)
	{
	case eType::MAP1:
		gridGame->SetFile("Resources/map/file_gameobject_map1.txt");
		TileMap->LoadMap(eType::MAP1);

		camera->SetAllowFollowSimon(true);

		camera->SetBoundary(0.0f, (float)(TileMap->GetMapWidth() - camera->GetWidth())); // set biên camera dựa vào kích thước map
		camera->SetBoundaryBackup(camera->GetBoundaryLeft(), camera->GetBoundaryRight()); // backup lại biên

		camera->SetPosition(0, 0);

		camera->SetAllowFollowSimon(true);

		simon->SetPosition(SIMON_POSITION_DEFAULT);
		simon->SetPositionBackup(SIMON_POSITION_DEFAULT);

		StateCurrent = 1;
		break;

	case eType::MAP2:

		gridGame->SetFile("Resources/map/file_gameobject_map2.txt");
		TileMap->LoadMap(eType::MAP2);

		camera->SetAllowFollowSimon(true);

		camera->SetPosition(0, 0);
		camera->SetBoundary(0, CAMERA_BOUNDARY_BEFORE_GO_GATE1_RIGHT); // biên camera khi chưa qua cửa
		camera->SetBoundaryBackup(0, CAMERA_BOUNDARY_BEFORE_GO_GATE1_RIGHT); // biên camera khi chưa qua cửa

		simon->SetPosition(SIMON_POSITION_DEFAULT);
		simon->SetPositionBackup(SIMON_POSITION_DEFAULT);
		break;
	}

	ResetResource();
}

void SceneGame::CheckCollision()
{
	CheckCollisionWeapon(listObj); // kt va chạm vũ khí với các object nền

	CheckCollisionSimonWithItem();
	CheckCollisionSimonWithObjectHidden();
	CheckCollisionSimonWithGate(); //va chạm với cửa

	if (!isProcessingGoThroughTheDoor1 && !isProcessingGoThroughTheDoor2) // ko phải đang xử lí qua cửa
		CheckCollisionWithEnemy(); // kt vũ khí với enemy và simon với enemy

	CheckCollisionWithBoss(); // kt vũ khí với enemy và simon với boss

}

void SceneGame::CheckCollisionWeapon(vector<GameObject*> listObj)
{

	for (auto& objWeapon : simon->mapWeapon)
	{
		if (objWeapon.second->GetFinish() == false) // Vũ khí đang hoạt động
		{
			for (UINT i = 0; i < listObj.size(); i++)
				if (objWeapon.second->GetLastTimeAttack() > listObj[i]->GetLastTimeAttacked()) // Nếu chưa xét va chạm của lượt attack này ở các frame trước
				{
					if (objWeapon.second->isCollision(listObj[i]) == true) // nếu có va chạm
					{
						bool RunEffectHit = false;
						GameObject *gameObj = listObj[i];
						switch (gameObj->GetType())
						{

						case eType::TORCH:
						{
							gameObj->SubHealth(1);
							listItem.push_back(GetNewItem(gameObj->GetId(), gameObj->GetType(), gameObj->GetX() + 5, gameObj->GetY()));// hiệu ứng hit
							RunEffectHit = true;
							break;
						}

						case eType::CANDLE:
						{
							gameObj->SubHealth(1);
							listItem.push_back(GetNewItem(gameObj->GetId(), gameObj->GetType(), gameObj->GetX() + 5, gameObj->GetY()));// hiệu ứng hit
							RunEffectHit = true;
							break;
						}

						case eType::GHOST:
						{
							gameObj->SubHealth(1);
							simon->SetScore(simon->GetScore() + 100);
							if (rand() % 2 == 1) // tỉ lệ 50%
							{
								listItem.push_back(GetNewItem(gameObj->GetId(), gameObj->GetType(), gameObj->GetX() + 5, gameObj->GetY()));
							}

							RunEffectHit = true;
							CountEnemyGhost--; // giảm số lượng Ghost đang hoạt động
							if (CountEnemyGhost == 0)
							{
								TimeWaitProcessCreateGhost = GetTickCount(); // set thời điểm hiện tại
								isWaitProcessCreateGhost = true;
								isAllowCheckTimeWaitProcessCreateGhost = true;
							}
							break;
						}

						case eType::PANTHER:
						{
							gameObj->SubHealth(1);
							simon->SetScore(simon->GetScore() + 200);
							if (rand() % 2 == 1) // tỉ lệ 50%
							{
								listItem.push_back(GetNewItem(gameObj->GetId(), gameObj->GetType(), gameObj->GetX() + 5, gameObj->GetY()));
							}
							RunEffectHit = true;
							CountEnemyPanther--; // giảm số lượng Panther đang hoạt động
							break;
						}

						case eType::BAT:
						{
							gameObj->SubHealth(1);
							simon->SetScore(simon->GetScore() + 200);
							if (rand() % 2 == 1) // tỉ lệ 50%
							{
								listItem.push_back(GetNewItem(gameObj->GetId(), gameObj->GetType(), gameObj->GetX() + 5, gameObj->GetY()));

							}

							RunEffectHit = true;
							CountEnemyGhost--; // giảm số lượng Ghost đang hoạt động
							if (CountEnemyGhost == 0)
							{
								TimeWaitProcessCreateGhost = GetTickCount(); // set thời điểm hiện tại
								isWaitProcessCreateGhost = true;
								isAllowCheckTimeWaitProcessCreateGhost = true;
							}
							break;
						}

						case eType::FISHMEN:
						{
							gameObj->SubHealth(1);
							simon->SetScore(simon->GetScore() + 300);
							if (rand() % 2 == 1) // tỉ lệ 50% 
								listItem.push_back(GetNewItem(gameObj->GetId(), gameObj->GetType(), gameObj->GetX() + 5, gameObj->GetY()));

							RunEffectHit = true;
							CountEnemyFishmen--; // giảm số lượng Fishmen đang hoạt động

							break;
						}

						case eType::PHANTOMBAT:
						{
							if (objWeapon.second->GetType() == eType::MORNINGSTAR)
							{
								MorningStar * morningstar = dynamic_cast<MorningStar *>(objWeapon.second);
								if (morningstar->GetLevel() > 0) // level 1 hoặc 2
									gameObj->SubHealth(24 / 8); // 8 hit chết
								else
									gameObj->SubHealth(24 / 12); // 12 hit chết

							}
							else
								gameObj->SubHealth(24 / 12); // 12 hit chết

							if (gameObj->GetHealth() == 0) // chết
							{
								for (int u = 0; u < 2; u++)
								{
									for (int v = 0; v < 3; v++)
									{
										listEffect.push_back(new Fire(gameObj->GetX() + v * FIRE_WIDTH, gameObj->GetY() + u * FIRE_HEIGHT - 10, 3)); // hiệu ứng lửa
										RunEffectHit = false;
									}
								}
								RunEffectHit = false;
								sound->Play(eSound::soundHit);
								listItem.push_back(new CrystalBall(CRYSTALBALL_DEFAULT_POSITION_X, CRYSTALBALL_DEFAULT_POSITION_y));

							}
							else
							{
								RunEffectHit = true;
							}
							break;
						}


						case eType::BRICK:
						{
							if (objWeapon.second->GetType() != eType::MORNINGSTAR) // nếu ko là MORNINGSTAR thì bỏ qua
								break;

							GameObject * gameObject = listObj[i];
							if (gameObject->GetHealth() > 0)
							{
								switch (gameObject->GetId())
								{
								case 39: // id 39 : brick 4 ô-> chỉ hiện effect
								{
									gameObject->SubHealth(1);
									HIT_ADD_EFFECT(listEffect, gameObject); // hiệu ứng hit
									BROKEN_BRICK_ADD_EFFECT(listEffect, gameObject); // hiệu ứng BrokenBrick
									sound->Play(eSound::soundBrokenBrick);
									break;
								}

								case 40: // id 40: brick 3 ô-> effect
								{
									gameObject->SubHealth(1);
									listItem.push_back(GetNewItem(gameObject->GetId(), gameObject->GetType(), gameObject->GetX(), gameObject->GetY()));
									HIT_ADD_EFFECT(listEffect, gameObject); // hiệu ứng hit
									BROKEN_BRICK_ADD_EFFECT(listEffect, gameObject); // hiệu ứng BrokenBrick								sound->Play(eSound::soundBrokenBrick);
									break;
								}

								case 72: // id 72: brick -> a bonus
								{
									gameObject->SubHealth(1);
									sound->Play(eSound::soundDisplayMonney);
									listItem.push_back(GetNewItem(gameObject->GetId(), gameObject->GetType(), gameObject->GetX(), gameObject->GetY()));
									HIT_ADD_EFFECT(listEffect, gameObject); // hiệu ứng hit
									BROKEN_BRICK_ADD_EFFECT(listEffect, gameObject); // hiệu ứng BrokenBrick								sound->Play(eSound::soundBrokenBrick);
									sound->Play(eSound::soundBrokenBrick);
									break;
								}

								case 51: // id 51: brick 2 -> effect
								{
									gameObject->SubHealth(1);
									HIT_ADD_EFFECT(listEffect, gameObject); // hiệu ứng hit
									BROKEN_BRICK_ADD_EFFECT(listEffect, gameObject); // hiệu ứng BrokenBrick								sound->Play(eSound::soundBrokenBrick);
									sound->Play(eSound::soundBrokenBrick);
									break;
								}

								case 104: // id 104: double shot
								{
									gameObject->SubHealth(1);

									listItem.push_back(GetNewItem(gameObject->GetId(), gameObject->GetType(), gameObject->GetX(), gameObject->GetY()));

									HIT_ADD_EFFECT(listEffect, gameObject); // hiệu ứng hit
									BROKEN_BRICK_ADD_EFFECT(listEffect, gameObject); // hiệu ứng BrokenBrick								sound->Play(eSound::soundBrokenBrick);
									sound->Play(eSound::soundBrokenBrick);
									break;
								}

								}
							}
							break;
						}
						default:
							break;
						}

						if (RunEffectHit)
						{
							listEffect.push_back(new Hit(listObj[i]->GetX() + 10, listObj[i]->GetY() + 14)); // hiệu ứng hit
							listEffect.push_back(new Fire(gameObj->GetX() - 5, gameObj->GetY() + 8)); // hiệu ứng lửa

							sound->Play(eSound::soundHit);

							if (objWeapon.second->GetType() == eType::DAGGER)
							{
								objWeapon.second->SetFinish(true);
							}

						}

						gameObj->SetLastTimeAttacked(objWeapon.second->GetLastTimeAttack()); // bị đánh trúng->update thời gian bị đánh lần cuối
					}
				}
		}
	}
}

void SceneGame::CheckCollisionSimonWithItem()
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

				case eType::SMALLHEART:
				{
					simon->SetHeartCollect(simon->GetHeartCollect() + 1);
					listItem[i]->SetFinish(true);
					sound->Play(eSound::soundCollectItem);
					break;
				}


				case eType::UPGRADEMORNINGSTAR:
				{
					MorningStar * objMorningStar = dynamic_cast<MorningStar*>(simon->mapWeapon[eType::MORNINGSTAR]);
					objMorningStar->UpgradeLevel(); // Nâng cấp vũ khí roi

					listItem[i]->SetFinish(true);
					simon->SetFreeze(true); // bật trạng thái đóng băng
					sound->Play(eSound::soundCollectWeapon);
					break;
				}

				/* Xử lí ăn tiền */
				case eType::MONEY_BAG_RED:
				{
					listItem[i]->SetFinish(true);
					sound->Play(eSound::soundCollectItem);
					simon->SetScore(simon->GetScore() + 100);
					listEffect.push_back(new EffectMoney(listItem[i]->GetX(), listItem[i]->GetY(), eType::EFFECT_MONEY_100));
					break;
				}

				case eType::MONEY_BAG_PURPLE:
				{
					listItem[i]->SetFinish(true);
					sound->Play(eSound::soundCollectItem);
					simon->SetScore(simon->GetScore() + 400);
					listEffect.push_back(new EffectMoney(listItem[i]->GetX(), listItem[i]->GetY(), eType::EFFECT_MONEY_400));
					break;
				}

				case eType::MONEY_BAG_WHITE:
				{
					listItem[i]->SetFinish(true);
					sound->Play(eSound::soundCollectItem);
					simon->SetScore(simon->GetScore() + 700);
					listEffect.push_back(new EffectMoney(listItem[i]->GetX(), listItem[i]->GetY(), eType::EFFECT_MONEY_700));
					break;
				}

				case eType::BONUS:
				{
					listItem[i]->SetFinish(true);
					sound->Play(eSound::soundCollectItem);
					simon->SetScore(simon->GetScore() + 1000);
					listEffect.push_back(new EffectMoney(listItem[i]->GetX(), listItem[i]->GetY(), eType::EFFECT_MONEY_1000));

					break;
				}
				/* Xử lí ăn tiền */

				case eType::POTROAST:
				{
					listItem[i]->SetFinish(true);
					sound->Play(eSound::soundCollectItem);
					simon->SetHealth(min(simon->GetHealth() + 6, SIMON_DEFAULT_HEALTH)); // tăng 6 đơn vị máu
					break;
				}

				case eType::ITEMDOUBLESHOT:
				{
					simon->SetIsUseDoubleShot(true); // bật chế độ Double Shot
					listItem[i]->SetFinish(true);
					sound->Play(eSound::soundCollectItem);
					break;
				}

				/* Vũ khí phụ của simon */
				case eType::ITEMDAGGER:
				{
					simon->ProcessWeaponCollect(eType::DAGGER);
					listItem[i]->SetFinish(true);
					break;
				}

				case eType::ITEMHOLYWATER:
				{
					simon->ProcessWeaponCollect(eType::HOLYWATER);
					listItem[i]->SetFinish(true);

					break;
				}

				case eType::STOPWATCH:
				{
					simon->ProcessWeaponCollect(eType::STOPWATCH);

					listItem[i]->SetFinish(true);
					break;
				}

				case eType::ITEMTHROWINGAXE:
				{
					simon->ProcessWeaponCollect(eType::THROWINGAXE);

					listItem[i]->SetFinish(true);
					break;
				}

				case eType::ITEMBOOMERANG:
				{
					simon->ProcessWeaponCollect(eType::BOOMERANG);
					listItem[i]->SetFinish(true);
					break;
				}
				/* Vũ khí phụ của simon */



				case eType::CRYSTALBALL:
				{
					listItem[i]->SetFinish(true);
					if (sound->isPlaying(eSound::music_PhantomBat))
					{
						sound->Stop(eSound::music_PhantomBat);
					}
					sound->Play(eSound::musicStateClear);

					isAllowProcessClearState3 = true;

					break;
				}



				case eType::INVISIBILITYPOTION:
				{
					sound->Play(eSound::soundInvisibilityPotion_Begin);
					isUseInvisibilityPotion = true;
					simon->SetTexture(TextureManager::GetInstance()->GetTexture(eType::SIMON_TRANS));
					listItem[i]->SetFinish(true);
					break;
				}

				case eType::CROSS:
				{
					isUseCross = true;
					TimeWaited_UseCross = 0;
					TimeWaited_UseCross_ChangeColorBackground = 0;

					board->SetTexture(TextureManager::GetInstance()->GetTexture(eType::BOARD_TRANS)); // đổi thành Board màu nền trong suốt

					/*Xóa hết enemy*/
					for (UINT k = 0; k < listEnemy.size(); k++)
					{
						GameObject * enemy = listEnemy[k];
						if (enemy->GetHealth() > 0) // còn máu
						{
							enemy->SetHealth(0);
							listEffect.push_back(new Fire(enemy->GetX() - 5, enemy->GetY() + 8)); // hiệu ứng lửa
						}
					}
					CountEnemyBat = 0;
					TimeWaitProcessCreateGhost = GetTickCount(); // set thời điểm hiện tại
					isWaitProcessCreateGhost = true;
					isAllowCheckTimeWaitProcessCreateGhost = true;

					CountEnemyFishmen = 0;

					CountEnemyPanther = 0;

					CountEnemyGhost = 0;
					TimeWaitProcessCreateGhost = GetTickCount(); // set thời điểm hiện tại
					isWaitProcessCreateGhost = true;
					isAllowCheckTimeWaitProcessCreateGhost = true;
					/*Xóa hết enemy*/

					listItem[i]->SetFinish(true);
					sound->Play(eSound::soundHolyCross);
					break;
				}

				default:
					DebugOut(L"[CheckCollisionSimonWithItem] Khong nhan dang duoc loai Item!\n");
					break;
				}



			}
		}





}

void SceneGame::CheckCollisionSimonWithObjectHidden()
{
	for (UINT i = 0; i < listObj.size(); i++)
	{
		if (listObj[i]->GetType() == eType::OBJECT_HIDDEN)
		{
			GameObject * gameObject = listObj[i];

			if (gameObject->GetHealth() > 0)
			{
				if (simon->isCollitionObjectWithObject(gameObject)) // có va chạm xảy ra
				{
					if (mapCurrent == eType::MAP1)
					{
						switch (gameObject->GetId())
						{
						case 7: // đụng trúng cửa
						{
							LoadMap(eType::MAP2);

							return;
							break;
						}

						case 8:
						{
							sound->Play(eSound::soundDisplayMonney);
							listItem.push_back(GetNewItem(gameObject->GetId(), gameObject->GetType(), simon->GetX(), simon->GetY()));
							break;
						}
						}
						gameObject->SubHealth(1);
					}

					if (mapCurrent == eType::MAP2)
					{
						switch (gameObject->GetId())
						{
						case 67: // đụng trúng box xác nhận simon đã qua GATE1
						{
							if (isProcessingGoThroughTheDoor1)
							{
								isDoneSimonGoThroughTheDoor1 = true;
								camera->SetAutoGoX(abs(GATE1_POSITION_CAM_AFTER_GO - camera->GetXCam()), SIMON_WALKING_SPEED);
								simon->SetPositionBackup(simon->GetX(), 0); // backup lại vị trí sau khi qua màn 
							}

							TimeCreateBat = GetTickCount();
							TimeWaitCreateBat = 3000;
							isAllowCreateBat = true;
							StateCurrent = 2;// set hiển thị đang ở state2
							camera->SetPositionBackup(camera->GetXCam(), camera->GetYCam());
							gameObject->SubHealth(1);
							DebugOut(L"Xac nhan qua xong cua!\n");
							break;
						}


						case 94: // đụng trúng box xác nhận simon đã qua GATE2
						{
							if (isProcessingGoThroughTheDoor2)
							{
								isDoneSimonGoThroughTheDoor2 = true;
								camera->SetAutoGoX(abs(GATE2_POSITION_CAM_AFTER_GO - camera->GetXCam()), SIMON_WALKING_SPEED);
								simon->SetPositionBackup(simon->GetX(), 0); // backup lại vị trí sau khi qua màn 
							}
							StateCurrent = 3;// set hiển thị đang ở state3
							camera->SetPositionBackup(camera->GetXCam(), camera->GetYCam());
							gameObject->SubHealth(1);

							DebugOut(L"Xac nhan qua xong cua 2!\n");
							break;
						}


						case 65: //id 65 : object ẩn->bonus
						{
							sound->Play(eSound::soundDisplayMonney);
							listItem.push_back(GetNewItem(gameObject->GetId(), gameObject->GetType(), simon->GetX(), simon->GetY()));
							gameObject->SetHealth(0);
							break;
						}


						case 66: //id 66: object ẩn -> chạm nước -> chết
						{
							simon->SetHealth(0);
							sound->Play(eSound::soundFallingDownWaterSurface);


							break;
						}

#pragma region Lên & xuống hồ nước phía trái

						case 41: // id 41: object ẩn -> bắt đầu xuống hồ nước
						{
							camera->SetPosition(camera->GetXCam(), CAMERA_POSITION_Y_LAKE);
							camera->SetBoundary(CAMERA_BOUNDARY_LAKE_LEFT, CAMERA_BOUNDARY_LAKE_RIGHT);
							simon->SetPosition(3150, 405);
							isAllowCreateBat = false;  // không cho tạo Bat
							isAllowCreateFishmen = true;
							gameObject->SetHealth(0);


							gridGame->Insert(GRID_INSERT_OBJECT__DIRAKHOIHONUOC_LEFT); // thêm object ẩn để có thể đi lên

							break;
						}
						case 45: // id 45: object ẩn -> trở lên trước khi xuống hồ nước
						{
							camera->SetPosition(camera->GetXCam(), 0);
							simon->SetPosition(3152, 345);
							isAllowCreateBat = true;  // cho tạo Bat
							isAllowCreateFishmen = false;
							TimeWaitCreateBat = 3000 + rand() % 1000;
							gameObject->SetHealth(0);

							gridGame->Insert(GRID_INSERT_OBJECT__DIXUONGHONUOC_LEFT); // thêm object ẩn để có thể đi xuống sau khi đã lên lại

							break;
						}
#pragma endregion

#pragma region Lên & xuống hồ nước phía Phải
						case 81: // id 81: object ẩn -> ra khỏi hồ nước phía phải
						{
							camera->SetPosition(camera->GetXCam(), 0);
							simon->SetPosition(3806, 361);
							isAllowCreateBat = true;
							isAllowCreateFishmen = false;
							TimeWaitCreateBat = 3000 + rand() % 1000;
							gameObject->SetHealth(0);
							gridGame->Insert(GRID_INSERT_OBJECT__DIXUONGHONUOC_RIGHT); // thêm object ẩn để có thể đi xuống sau khi đã lên lại
							gridGame->Insert(GRID_INSERT_OBJECT__DIXUONGHONUOC_LEFT); // thêm object ẩn để có thể đi xuống sau khi đã lên lại
							break;
						}


						case 86: // id 86: object ẩn -> vào hồ nước phía phải
						{
							camera->SetPosition(camera->GetXCam(), CAMERA_POSITION_Y_LAKE);
							simon->SetPosition(3825, 450);
							isAllowCreateBat = false;  // không cho tạo Bat
							isAllowCreateFishmen = true;

							gameObject->SetHealth(0);

							gridGame->Insert(GRID_INSERT_OBJECT__DIRAKHOIHONUOC_RIGHT); // thêm object ẩn để có thể đi xuống sau khi đã lên lại

							break;
						}
#pragma endregion




						case 124: //id 124 : kích hoạt boss
						{
							boss->Start();

							camera->SetBoundary(camera->GetBoundaryRight(), camera->GetBoundaryRight());
							camera->SetAllowFollowSimon(false);

							if (sound->isPlaying(eSound::musicState1))
							{
								sound->Stop(eSound::musicState1);
							}
							sound->Play(eSound::music_PhantomBat, true);

							gameObject->SetHealth(0);
							break;
						}

						}

					}

				}
			}
		}
	}


}

void SceneGame::CheckCollisionWithEnemy()
{
	CheckCollisionWeapon(listEnemy); // enemy bt
	CheckCollisionSimonWithEnemy();
}

void SceneGame::CheckCollisionSimonWithEnemy()
{
	if (GetTickCount() - simon->untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		simon->untouchable_start = 0;
		simon->untouchable = false;
	}

	if (isUseInvisibilityPotion) // ko sử dụng thuốc tàng hình mới xét va chạm
	{
		return;
	}

	if (simon->untouchable == false) // đã tắt chế độ ko cho chạm
	{
#pragma region Va chạm với Enemy bình thường
		for (UINT i = 0; i < listEnemy.size(); i++)
		{
			GameObject * gameobj = dynamic_cast<GameObject *> (listEnemy[i]);
			if (gameobj->GetHealth() > 0) // còn sống
			{
				LPCOLLISIONEVENT e = simon->SweptAABBEx(gameobj);
				bool isCollision = false;
				if (e->t > 0 && e->t <= 1) // có va chạm
				{
					simon->SetHurt(e);
					isCollision = true;
				}
				if (isCollision == false && simon->checkAABB(gameobj) == true)
				{
					LPCOLLISIONEVENT e = new CollisionEvent(1.0f, (float)-simon->GetDirection(), 0.0f, NULL);
					simon->SetHurt(e);
					isCollision = true;
				}

				if (isCollision)
				{
					if (gameobj->GetType() == eType::BAT)
					{
						listEffect.push_back(new Fire(gameobj->GetX() - 5, gameobj->GetY() + 8)); // hiệu ứng lửa
						gameobj->SetHealth(0);
					}
					return; // giảm chi phí duyệt, vì nếu có va chạm thì cũng đang untouchable
				}
			}
		}
#pragma endregion 
	}

	if (simon->untouchable == false)
	{
#pragma region Collision With Weapon of Enemy
		for (UINT i = 0; i < listWeaponOfEnemy.size(); i++)
		{
			if (listWeaponOfEnemy[i]->GetFinish() == false)
			{
				LPCOLLISIONEVENT e = simon->SweptAABBEx(listWeaponOfEnemy[i]);
				if (e->t > 0 && e->t <= 1) // có va chạm
				{
					simon->SetHurt(e);
					return; // giảm chi phí duyệt, vì nếu có va chạm thì cũng đang untouchable
				}

				if (simon->checkAABB(listWeaponOfEnemy[i]) == true)
				{
					LPCOLLISIONEVENT e = new CollisionEvent(1.0f, (float)-simon->GetDirection(), 0.0f, NULL);
					simon->SetHurt(e);
					return;
				}
			}
		}
#pragma endregion
	}

}

void SceneGame::CheckCollisionSimonWithGate()
{
	for (UINT i = 0; i < listObj.size(); i++)
	{
		if (listObj[i]->GetType() == eType::GATE)
		{
			if (simon->isCollitionObjectWithObject(listObj[i]))
			{
				Gate* objGate = dynamic_cast<Gate*>(listObj[i]);

				 
				if (mapCurrent == eType::MAP2)
				{
					switch (objGate->GetId())
					{
					case 64: // gate 1
					{
						if (objGate->GetStart() == 0)
						{
							//di chuyển camera đến GATE1_POSITION_CAM_BEFORE_GO = 2825.0f
							camera->SetBoundary(camera->GetBoundaryLeft(), camera->GetBoundaryRight() + 9999.0f);// mở biên phải rộng ra thêm để chạy AutoGo
							camera->SetAutoGoX(abs(GATE1_POSITION_CAM_BEFORE_GO - camera->GetXCam()), SIMON_WALKING_SPEED);

#pragma region Stop simon
							simon->SetSpeed(0, simon->GetVy()); // cho simon dừng, tránh trường hợp không vào được trạng thái stop trong KeyState()
							simon->isWalking = 0;
							if (simon->isSitting == true) // nếu simon đang ngồi
							{
								simon->isSitting = 0; // hủy trạng thái ngồi
								simon->SetY(simon->GetY() - PULL_UP_SIMON_AFTER_SITTING); // kéo simon lên
							}
#pragma endregion

							isProcessingGoThroughTheDoor1 = true; // bật trạng thái xử lí qua cửa
							isDoneSimonGoThroughTheDoor1 = false;
							objGate->Start();

							DebugOut(L"Simon dung trung cua!\n");


							break;
						}
						break;
					}

					case 93: // gate 2
					{
						if (objGate->GetStart() == 0)
						{
							camera->SetBoundary(camera->GetBoundaryLeft(), CAMERA_BOUNDARY_BOSS_RIGHT);// mở biên phải rộng ra thêm để chạy AutoGo
							camera->SetAutoGoX(abs(GATE2_POSITION_CAM_BEFORE_GO - camera->GetXCam()), SIMON_WALKING_SPEED);

#pragma region Stop simon
							simon->SetSpeed(0, simon->GetVy()); // cho simon dừng, tránh trường hợp không vào được trạng thái stop trong KeyState()
							simon->isWalking = 0;
							if (simon->isSitting == true) // nếu simon đang ngồi
							{
								simon->isSitting = 0; // hủy trạng thái ngồi
								simon->SetY(simon->GetY() - PULL_UP_SIMON_AFTER_SITTING); // kéo simon lên
							}
#pragma endregion

							isProcessingGoThroughTheDoor2 = true; // bật trạng thái xử lí qua cửa
							isDoneSimonGoThroughTheDoor2 = false;

							isAllowCreateBat = false; // tắt tạo Bat

							objGate->Start();
							DebugOut(L"Simon dung trung cua 2!\n");

							if (boss == NULL)
								boss = new PhantomBat(simon, camera, &listWeaponOfEnemy);

							break;
						}
						break;
					}




					default:
						break;
					}

				}

				

			}
		}
	}
}

void SceneGame::CheckCollisionWithBoss()
{
	if (boss == NULL)
		return;

	if (boss->GetHealth() <= 0)
		return;

	vector<GameObject*> listObj{ boss };
	CheckCollisionWeapon(listObj); // enemy bt

	if (isUseInvisibilityPotion) // ko sử dụng thuốc tàng hình mới xét va chạm
	{
		return;
	}

	if (GetTickCount() - simon->untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		simon->untouchable_start = 0;
		simon->untouchable = false;
	}

	if (simon->untouchable == false) // đã tắt chế độ ko cho chạm
	{
		if (boss->GetHealth() > 0) // còn sống
		{
			LPCOLLISIONEVENT e = simon->SweptAABBEx(boss);
			if (e->t > 0 && e->t <= 1) // có va chạm
			{
				simon->SetHurt(e);
				return; // giảm chi phí duyệt, vì nếu có va chạm thì cũng đang untouchable
			}
			if (simon->checkAABB(boss) == true)
			{
				LPCOLLISIONEVENT e = new CollisionEvent(1.0f, (float)-simon->GetDirection(), 0.0f, NULL);
				simon->SetHurt(e);
				return;
			}
		}

	}
}

Item * SceneGame::GetNewItem(int Id, eType Type, float X, float Y)
{
	if (mapCurrent == eType::MAP1)
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
	}

	if (mapCurrent == eType::MAP2)
	{
		if (Type == eType::CANDLE)
		{
			switch (Id)
			{
			case 2:
				return new MoneyBag(X, Y, eType::MONEY_BAG_WHITE);
				break;

			case 40: case 71:
				return new ItemHolyWater(X, Y);
				break;

			case 76:
				return new ItemStopWatch(X, Y);
				break;

			case 109:
				return new InvisibilityPotion(X, Y);
				break;

			case 111:
				return new ItemThrowingAxe(X, Y);
				break;

			case 23: case 98:
				return new Cross(X, Y);
				break;

			default:
			{
				int random = rand() % 10;
				switch (random)
				{
				case 0:
					return new MoneyBag(X, Y, eType::MONEY_BAG_RED);
					break;
				case 1:
					return new MoneyBag(X, Y, eType::MONEY_BAG_WHITE);
					break;
				case 2:
					return new MoneyBag(X, Y, eType::MONEY_BAG_PURPLE);
					break;
				default:
					return new SmallHeart(X, Y);
					break;
				}
				break;
			}
			}

		}


		if (Type == eType::GHOST || Type == eType::PANTHER || Type == eType::BAT || Type == eType::FISHMEN)
		{
			int random = rand() % 15;

			if (random == 4)
			{
				MorningStar * morningstar = dynamic_cast<MorningStar*>(simon->mapWeapon[eType::MORNINGSTAR]);
				while (morningstar->GetLevel() == 2 && random == 4)
				{
					random = rand() % 15;
				}
			}


			switch (random)
			{
			case 0:
				return new LargeHeart(X, Y);
				break;
			case 1:
				return new SmallHeart(X, Y);
				break;
			case 2:
				return new ItemDagger(X, Y);
				break;
			case 3:
				return new Bonus(X, Y);
				break;
			case 4:
				return new UpgradeMorningStar(X, Y);
				break;
			case 5:
				return new ItemHolyWater(X, Y);
				break;
			case 6:
				return new ItemStopWatch(X, Y);
				break;
			case 7:
				return new ItemThrowingAxe(X, Y);
				break;
			case 8:
				return new InvisibilityPotion(X, Y);
				break;
			case 9:
				return new ItemBoomerang(X, Y);
				break;
			default: // còn lại là SmallHeart
				return new SmallHeart(X, Y);
				break;
			}
		}

		if (Type == eType::BRICK)
		{
			switch (Id)
			{
			case 40:
				return new PotRoast(X, Y);
				break;
			case 72:
				return new Bonus(X, Y);
				break;

			case 104: // Double shot
				return new ItemDoubleShot(X, Y);
				break;


			default:
				return new SmallHeart(X, Y);
				break;
			}

		}


		if (Type == eType::OBJECT_HIDDEN)
		{
			if (Id == 65)
				return new Bonus(3763.0f, 587.0f);

		}

	}
	 
	return new LargeHeart(X, Y);
}

void SceneGame::ProcessClearState3(DWORD dt)
{
	if (isAllowProcessClearState3)
	{
		switch (StatusProcessClearState3)
		{
		case CLEARSTATE3_PROCESS_HEALTH:
		{
			TimeWaited_ClearState3 += dt;
			if (TimeWaited_ClearState3 >= CLEARSTATE3_LIMITTIMEWAIT_PROCESS_HEALTH)
			{
				TimeWaited_ClearState3 = 0;

				if (simon->GetHealth() < SIMON_DEFAULT_HEALTH)
				{
					simon->SetHealth(simon->GetHealth() + 1);
				}
				else
				{
					StatusProcessClearState3 = CLEARSTATE3_PROCESS_GETSCORE_TIME;
				}
			}
			break;
		}

		case CLEARSTATE3_PROCESS_GETSCORE_TIME:
		{
			TimeWaited_ClearState3 += dt;
			if (TimeWaited_ClearState3 >= CLEARSTATE3_LIMITTIMEWAIT_PROCESS_GETSCORE_TIME)
			{
				TimeWaited_ClearState3 = 0;

				if (GAME_TIME_MAX - gameTime->GetTime() > 0) // thời gian còn lại lớn hơn 0
				{
					simon->SetScore(simon->GetScore() + 10); // mỗi giây +10 điểm
					gameTime->SetTime(gameTime->GetTime() + 1);// giảm giây còn lại
					sound->Play(eSound::soundGetScoreTimer, true);
				}
				else
				{
					StatusProcessClearState3 = CLEARSTATE3_PROCESS_GETSCORE_HEART;
					TimeWaited_ClearState3 = 0;
					sound->Stop(eSound::soundGetScoreTimer);
				}
			}

			break;
		}

		case CLEARSTATE3_PROCESS_GETSCORE_HEART:
		{
			TimeWaited_ClearState3 += dt;
			if (TimeWaited_ClearState3 >= CLEARSTATE3_LIMITTIMEWAIT_PROCESS_GETSCORE_HEART)
			{
				TimeWaited_ClearState3 = 0;

				if (simon->GetHeartCollect() > 0) // thời gian còn lại lớn hơn 0
				{
					simon->SetScore(simon->GetScore() + 100); // mỗi giây +100 điểm
					simon->SetHeartCollect(simon->GetHeartCollect() - 1); // giảm 1 heart
					sound->Play(eSound::soundGetScoreHeart, true);
				}
				else
				{
					sound->Stop(eSound::soundGetScoreHeart);
					StatusProcessClearState3 = CLEARSTATE3_PROCESS_DONE;

				}
			}

			break;
		}

		case CLEARSTATE3_PROCESS_DONE:
		{
			TimeWaited_ClearState3 += dt;
			if (TimeWaited_ClearState3 >= CLEARSTATE3_LIMITTIMEWAIT_PROCESS_OPENGAMEOVER)
			{
				isAllowProcessClearState3 = false; // tắt clear state
				isGameOver = true; // bật bảng hiện gameover
			}
			break;
		}

		default:
			break;
		}
	}
}

void SceneGame::ProcessInvisibilityPotion(DWORD dt)
{
	if (isUseInvisibilityPotion)
	{
		TimeWaited_InvisibilityPotion += dt;
		if (TimeWaited_InvisibilityPotion >= INVISIBILITYPOTION_LIMITTIMEWAIT)
		{
			isUseInvisibilityPotion = false; // kết thúc
			TimeWaited_InvisibilityPotion = 0;
			sound->Play(eSound::soundInvisibilityPotion_End);

			simon->SetTexture(TextureManager::GetInstance()->GetTexture(eType::SIMON));
		}
	}
}

void SceneGame::ProcessCross(DWORD dt)
{
	if (isUseCross)
	{
		/* xử lí thời gian hoạt động*/
		TimeWaited_UseCross += dt;
		if (TimeWaited_UseCross >= CROSS_LIMITTIME)
		{
			isUseCross = false;
			D3DCOLOR_BACKGROUND = COLOR_BACKGROUND_DEFAULT; // trả về màu nền mặc định
			board->SetTexture(TextureManager::GetInstance()->GetTexture(eType::BOARD)); // đổi thành Board màu bt
		}
		else
		{
			/*Xử lí đổi màu nền*/
			TimeWaited_UseCross_ChangeColorBackground += dt;
			if (TimeWaited_UseCross_ChangeColorBackground >= LimitTimeWait_UseCross_ChangeColorBackground)
			{
				TimeWaited_UseCross_ChangeColorBackground = 0;
				LimitTimeWait_UseCross_ChangeColorBackground = rand() % 100;
				/*Đổi màu nền*/
				if (D3DCOLOR_BACKGROUND == COLOR_BACKGROUND_DEFAULT)
				{
					D3DCOLOR_BACKGROUND = CROSS_COLOR_BACKGROUND;
				}
				else
				{
					D3DCOLOR_BACKGROUND = COLOR_BACKGROUND_DEFAULT;
				}
			}
		}
	}
}

void SceneGame::ReplayMusicGame()
{
	sound->StopAll();// tắt hết nhạc
	sound->Play(eSound::musicState1, true); // mở lại nhạc nền
}
