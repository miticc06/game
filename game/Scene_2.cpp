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

	if (camera->GetIsAutoGoX()) // camera đang chế độ tự đi thì ko xét phím
		return;

	if (simon->isJumping && simon->isWalking)
		return;

	//if (simon->isHurting && simon->isOnStair)
	//{
	//	simon->isHurting = 0;
	//}

	if (simon->isHurting)
		return;

	if (!simon->isJumping)
	{


		if (Game::GetInstance()->IsKeyDown(DIK_UP))
		{
			if (!simon->isOnStair) // chưa trên thang
			{
				for (UINT i = 0; i < listObj.size(); i++)
					if (listObj[i]->GetType() == eType::STAIR_BOTTOM)
					{
						if (simon->isCollitionObjectWithObject(listObj[i])) // nếu va chạm với STAIR BOTOM
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



							//simon->SetPosition(gameobj->GetX(), simon->GetY()); // đặt lại vị trí X của simon
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
			if (Game::GetInstance()->IsKeyDown(DIK_DOWN)) // ngược lại nếu nhấn nút xuống
			{
				if (!simon->isOnStair) // chưa trên cầu thang
				{
					int CountCollisionTop = 0;
					for (UINT i = 0; i < listObj.size(); i++)
						if (listObj[i]->GetType() == eType::STAIR_TOP)
						{
							if (simon->isCollitionObjectWithObject(listObj[i])) // nếu va chạm với STAIR TOP
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
		simon->SetPosition(2830.0f, 0);
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
		isDoneSimonGoThroughTheDoor1 = false; 


		isDoneSimonGoThroughTheDoor1 = true;
	//	camera->SetAutoGoX(abs(ViTriCameraDiChuyenSauKhiQuaCua - camera->GetXCam()), SIMON_WALKING_SPEED);
		isDoneCameraGoThroughTheDoor1 = false;
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



	if (KeyCode == DIK_9) // đứng ngay cầu thang gần xuoosg hồ nước
	{
		DebugOut(L"[SET POSITION SIMON] x = .... \n");
		simon->SetPosition(3084.0f, 310.0f);


		camera->SetBoundary(3073, camera->GetBoundaryRight() + 1023);// mở biên phải rộng ra thêm để chạy AutoGo
		//camera->SetAutoGoX(abs(ViTriCameraDiChuyenTruocKhiQuaCua - camera->GetXCam()), SIMON_WALKING_SPEED);
		simon->Stop(); // cho simon dừng, tránh trường hợp không vào được trạng thái stop trong KeyState()
		isProcessingGoThroughTheDoor1 = true; // bật trạng thái xử lí qua cửa
		isDoneSimonGoThroughTheDoor1 = false;


		isDoneSimonGoThroughTheDoor1 = true;
		//	camera->SetAutoGoX(abs(ViTriCameraDiChuyenSauKhiQuaCua - camera->GetXCam()), SIMON_WALKING_SPEED);
		isDoneCameraGoThroughTheDoor1 = false;
		simon->SetPositionBackup(simon->GetX(), 0); // backup lại vị trí sau khi qua màn 
		TimeCreateBat = GetTickCount();
		TimeWaitCreateBat = 2000;
		isAllowCreateBat = true;
		StateCurrent = 2;// set hiển thị đang ở state2
		camera->SetPositionBackup(camera->GetXCam(), camera->GetYCam());
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
		simon->SetAutoGoX(simon->GetDirection(), -1, 200, SIMON_WALKING_SPEED);
	}


	if (KeyCode == DIK_G) // add ghost 
	{
		listEnemy.push_back(new Ghost(200, 200, 1));
	}

	if (KeyCode == DIK_C) // test AUTO GO CAM
	{
		camera->SetAutoGoX(200.0f, SIMON_WALKING_SPEED);
	}

	if (KeyCode == DIK_T) // change isCameraFollowSimon
	{
		if (camera->AllowFollowSimon())
			camera->SetAllowFollowSimon(0);
		else
			camera->SetAllowFollowSimon(1);

	}

	if (KeyCode == DIK_B) // create BAT
	{
		listEnemy.push_back(new Bat(camera->GetXCam() + camera->GetWidth() - 100, simon->GetY() + 20, -1));

	}


	if (KeyCode == DIK_H) // create hollywater
	{
		simon->_weaponSub = new HolyWater();

	}

	if (KeyCode == DIK_F) // create hollywater
	{
		simon->SetHealth(16);
		simon->SetLives(9999);
		simon->SetHeartCollect(9999);
		_gameTime->SetTime(0);
		simon->_weaponSub = new HolyWater();

	}


	if (KeyCode == DIK_H)
	{
		simon->SetHealth(9999);
		simon->SetLives(9999);
		simon->SetHeartCollect(9999);
		_gameTime->SetTime(0);
		simon->_weaponSub = new HolyWater();
	}



	if (KeyCode == DIK_M) // tesst fishmen
	{ 
		float vtx = simon->GetX() + 100;
		float vty = 805;
		listEnemy.push_back(new Fishmen(vtx, vty, -1));

		listEffect.push_back(new Steam(vtx, vty, 1));
		listEffect.push_back(new Steam(vtx, vty, 2));
		listEffect.push_back(new Steam(vtx, vty, 3));

		sound->Play(eSound::soundSplashwater);
	}


	if (simon->isAutoGoX == true) // đang chế độ tự đi thì ko xét phím
		return;

	if (camera->GetIsAutoGoX()) // camera đang chế độ tự đi thì ko xét phím
		return;


	if (simon->isHurting)
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
		if (simon->_weaponSub != NULL && simon->_weaponSub->GetFinish() == true)
		{
			bool isOk = false;
			switch (simon->_weaponSub->GetType())
			{
			case eType::STOPWATCH:
				if (simon->GetHeartCollect() >= 5)
				{
					simon->SetHeartCollect(simon->GetHeartCollect() - 5); // giảm 5 heart 
					isOk = true;
				}
				break;

			default:
				if (simon->GetHeartCollect() > 0)
				{
					simon->SetHeartCollect(simon->GetHeartCollect() - 1); // giảm 1 heart 
					isOk = true;
				}				
				break;
			}

			if (isOk)
				simon->Attack(simon->_weaponSub); 
		}
	}

	if (KeyCode == DIK_D)
	{
		listItem.push_back(new ItemDagger(simon->GetX(), simon->GetY()));

	}


	if (KeyCode == DIK_S)
	{
		listItem.push_back(new ItemStopWatch(simon->GetX(), simon->GetY()));

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
			simon->SetSpeed(SIMON_WALKING_SPEED * simon->GetDirection(), vy - SIMON_VJUMP);
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

	if (simon == NULL)
		simon = new Simon();

	if (_gameTime == NULL)
		_gameTime = new GameTime();

	TileMap = new Map();
	TileMap->LoadMap(eType::MAP2);

	camera = new Camera(Window_Width, Window_Height);
	camera->SetPosition(0, 0);
	camera->SetBoundary(0, BienPhaiCameraKhiChuaQuaCua1); // biên camera khi chưa qua cửa

	board = new Board(0, 0);

	simon->SetPosition(SIMON_POSITION_DEFAULT);
	simon->SetPositionBackup(SIMON_POSITION_DEFAULT);

	gridGame = new Grid();
	gridGame->ReadFileToGrid("Resources/map/Obj_2.txt"); // đọc các object từ file vào Grid



	listItem.clear();
	listEffect.clear();
	listEnemy.clear();
	// chưa thu hồi bộ nhớ?

	// bật nhạc game
	if (sound->isPlaying(eSound::musicState1) == false)
		sound->Play(eSound::musicState1, true);

	CountEnemyGhost = 0;
	TimeCreateGhost = 0;
	isWaitProcessCreateGhost = false; // lúc đầu thì không cần chờ
	CountEnemyGhost = 0;

	isProcessingGoThroughTheDoor1 = false; // ban đầu chưa cần xử lí qua cửa
	isDoneSimonGoThroughTheDoor1 = false;

	isAllowRenewPanther = true;
	CountEnemyPanther = 0;

	isAllowCreateFishmen = false;
	TimeCreateFishmen = 0;
	TimeWaitCreateFishmen = 0;
	CountEnemyFishmen = 0;

	CountEnemyPanther = 0;



	TimeCreateBat = 0;
	TimeWaitCreateBat = 0;
	isAllowCreateBat = 0;

	StateCurrent = 1;

	isStopWatch = 0;
}
 
void Scene_2::ResetResource()
{
	SAFE_DELETE(gridGame);
	gridGame = new Grid();
	gridGame->ReadFileToGrid("Resources/map/Obj_2.txt"); // đọc lại các object từ list

	listItem.clear();
	listEffect.clear();
	listEnemy.clear();

	CountEnemyGhost = 0;
	TimeCreateGhost = 0;
	isWaitProcessCreateGhost = false; // lúc đầu thì không cần chờ
	CountEnemyGhost = 0;

	_gameTime->SetTime(0); // đếm lại từ 0
	sound->Stop(eSound::musicState1); // tắt nhạc nền
	sound->Play(eSound::musicState1, true); // mở lại nhạc nền


	isAllowRenewPanther = true;
	CountEnemyPanther = 0;

	isAllowCreateFishmen = false;
	TimeCreateFishmen = 0;
	TimeWaitCreateFishmen = 0;
	CountEnemyFishmen = 0;


	TimeCreateBat = 0;
	TimeWaitCreateBat = 0;
	isAllowCreateBat = 0;

	isStopWatch = 0;
	camera->SetAllowFollowSimon(true);
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

#pragma region Process_Gametime_OR_Health
	if (_gameTime->GetTime() >= GAME_TIME_SCENE2 || simon->GetHealth() <= 0) // hết thời gian hoặc hết máu
	{
		sound->Play(eSound::musicLifeLost);
		if (simon->GetLives() == 0)
			return;
		bool result = simon->LoseLife(); // đã khôi phục x,y
		camera->RestorePosition(); // khôi phục vị trí camera;
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

#pragma region Process Gate 1

	if (isProcessingGoThroughTheDoor1)
	{
		if (isDoneSimonGoThroughTheDoor1 == false) // simon chưa hoàn thành việc qua cửa
		{
			if (camera->GetXCam() >= ViTriCameraDiChuyenTruocKhiQuaCua) // camera đã AutoGo xong đến vị trí 2825.0f
			{

				simon->SetAutoGoX(1, 1, abs(3143.0f - simon->GetX()), SIMON_WALKING_SPEED); // bắt đầu cho simon di chuyển tự động đến vị trí tiếp theo
			}
		}
		else
		{
			if (camera->GetXCam()/* + 1.0f */>= ViTriCameraDiChuyenSauKhiQuaCua)
			{
				camera->SetBoundary(ViTriCameraDiChuyenSauKhiQuaCua, camera->GetBoundaryRight());
				camera->SetAllowFollowSimon(true);
				isProcessingGoThroughTheDoor1 = false; // xong việc xử lí qua cửa 1
				camera->StopAutoGoX(); // dừng việc tự di chuyển
			}
		}
	}

#pragma endregion


#pragma region Process_StopWatch
	if (simon->_weaponSub != NULL && simon->_weaponSub->GetType() == eType::STOPWATCH)
	{
		if (simon->_weaponSub->GetFinish() == false) //stopwatch chưa kt
		{
			isStopWatch = true;
		}
		else
			isStopWatch = false;
	}
	else
		isStopWatch = false;
#pragma endregion



	gridGame->GetListObject(listObj, camera); // lấy hết các object "còn Alive" trong vùng camera;

	//DebugOut(L"[GRID] size = %d\n", listObj.size());

	simon->Update(dt, camera, &listObj);

	if (camera->AllowFollowSimon())
	{
		camera->SetPosition(simon->GetX() - Window_Width / 2 + 30, camera->GetYCam()); // cho camera chạy theo simon
	}
	camera->Update(dt);



	//	Cần tạo khoảng chờ khi tạo bot




#pragma region Process_Region_Create_Enemy_Ghost

//	DebugOut(L"now = %d - listenemy = %d\n", CountEnemyGhost, listEnemy.size());
	DWORD now = GetTickCount();



	if (isWaitProcessCreateGhost == false) // nếu không phải chờ xử lí thì vào xử lí
	{
#pragma region Vùng 1 & Vùng 2
		if ((simon->GetX() >= -16.0f /* 0.0f */ && simon->GetX() <= 825.0f) || (simon->GetX() > 2200 && simon->GetX() < 2775))
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
				listEnemy.push_back(new Panther(1398.0f, 225.0f, directionPanther, directionPanther == -1 ? 20.0f : 9.0f));
				listEnemy.push_back(new Panther(1783.0f, 160.0f, directionPanther, directionPanther == -1 ? 278.0f : 180.0f));
				listEnemy.push_back(new Panther(1923.0f, 225.0f, directionPanther, directionPanther == -1 ? 68.0f : 66.0f));
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
			listEnemy.push_back(new Bat(camera->GetXCam() + camera->GetWidth() - 10, simon->GetY() + 40, -1));

			TimeWaitCreateBat = 4000 + (rand() % 3000);
		}
	}

#pragma endregion


#pragma region Create Fishmen



	if (isAllowCreateFishmen && CountEnemyFishmen<=2)
	{
		DWORD now = GetTickCount();
		if (now - TimeCreateFishmen >= TimeWaitCreateFishmen) // đủ thời gian chờ
		{
			TimeCreateFishmen = now; // đặt lại thời gian đã tạo

			float vtx = 0;

			if (FISHMEN_ZONE_1_LEFT < simon->GetX() && simon->GetX() <= FISHMEN_ZONE_1_RIGHT)
			{
				//vtx = (rand() % 2) ? (FISHMEN_POS_2) : ((rand() % 2) ? (FISHMEN_POS_3) : (FISHMEN_POS_4));
				vtx = (rand() % 2) ? (FISHMEN_POS_3) : (FISHMEN_POS_4);

			}

			if (FISHMEN_ZONE_2_LEFT < simon->GetX() && simon->GetX() <= FISHMEN_ZONE_2_RIGHT)
			{
				vtx = (rand() % 2) ? (FISHMEN_POS_1) : ((rand() % 2) ? (FISHMEN_POS_3) : (FISHMEN_POS_4));

			} 

			if (FISHMEN_ZONE_3_LEFT < simon->GetX() && simon->GetX() <= FISHMEN_ZONE_3_RIGHT)
			{
				vtx = (rand() % 2) ?  (FISHMEN_POS_4) : (FISHMEN_POS_5);

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

			
			float vty = 805;
			listEnemy.push_back(new Fishmen(vtx, vty, directionFishmen));
			
			CountEnemyFishmen++;

			listEffect.push_back(new Steam(vtx, vty, 1));
			listEffect.push_back(new Steam(vtx, vty, 2));
			listEffect.push_back(new Steam(vtx, vty, 3)); 
			sound->Play(eSound::soundSplashwater);
			 
			 
			TimeWaitCreateFishmen = 2000 + (rand() % 2000);
		}
	}

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

	if (!isStopWatch)
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
							if (CountEnemyGhost == 0)
							{
								TimeWaitProcessCreateGhost = GetTickCount(); // set thời điểm hiện tại
								isWaitProcessCreateGhost = true;
								isAllowCheckTimeWaitProcessCreateGhost = true;
							}
						}
					}
					else
						enemy->Update(dt, &listObj);
					break;
				}

				case eType::PANTHER:
				{
					Panther * objPanther = dynamic_cast<Panther *>(enemy);
					if (camera->checkObjectInCamera(
						objPanther->GetX(),
						objPanther->GetY(),
						objPanther->GetWidth(),
						objPanther->GetHeight())) // nếu Panther nằm trong camera thì update
						// vì do Grid load object nền (Brick) dựa vào vùng camera, nên có nguy cơ khiến 1 số object Panther không xét được va chạm đất.
					{
						objPanther->Update(dt, simon, &listObj);
					}
					else // nằm ngoài camera
					{
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
					if (camera->checkObjectInCamera(
						enemy->GetX(),
						enemy->GetY(),
						enemy->GetWidth(),
						enemy->GetHeight())) // nếu bat nằm trong camera thì update
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
					if (camera->checkObjectInCamera(
						enemy->GetX(),
						enemy->GetY(),
						enemy->GetWidth(),
						enemy->GetHeight())) // nếu nằm trong camera thì update
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

	board->Render(camera, simon, StateCurrent, simon->_weaponSub, GAME_TIME_SCENE2 - _gameTime->GetTime());



}


void Scene_2::CheckCollision()
{
	CheckCollisionWeapon(listObj); // kt va chạm vũ khí với các object nền

	CheckCollisionSimonWithItem();
	CheckCollisionSimonWithObjectHidden();
	CheckCollisionSimonWithGate(); //va chạm với cửa

	CheckCollisionWithEnemy(); // kt vũ khí với enemy và simon với enemy

}

void Scene_2::CheckCollisionWeapon(vector<GameObject*> listObj)
{
	// main weapon
	if (simon->_weaponMain->GetFinish() == false) // Vũ khí đang hoạt động
	{
		for (UINT i = 0; i < listObj.size(); i++) // đã kt object còn sống hay k trong hàm va chạm của vũ khí
			if (simon->_weaponMain->isCollision(listObj[i]) == true) // nếu có va chạm thì kt kiểu
			{
				bool RunEffectHit = false;
				GameObject *gameObj = listObj[i];
				switch (gameObj->GetType())
				{
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
					simon->SetScore(simon->GetScore() + 200);
					if (rand() % 2 == 1) // tỉ lệ 50% 
						listItem.push_back(GetNewItem(gameObj->GetId(), gameObj->GetType(), gameObj->GetX() + 5, gameObj->GetY())); 

					RunEffectHit = true;
					CountEnemyFishmen--; // giảm số lượng Fishmen đang hoạt động

					break;
				}

				default:
					break;
				}

				if (RunEffectHit)
				{
					listEffect.push_back(new Hit((int)listObj[i]->GetX() + 10, (int)listObj[i]->GetY() + 14)); // hiệu ứng hit
					listEffect.push_back(new Fire((int)gameObj->GetX() - 5, (int)gameObj->GetY() + 8)); // hiệu ứng lửa

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
				GameObject *gameObj = listObj[i];

				switch (gameObj->GetType())
				{
				case eType::CANDLE:
				{ 
					gameObj->SubHealth(1);
					listItem.push_back(GetNewItem(gameObj->GetId(), gameObj->GetType(), gameObj->GetX() + 5, gameObj->GetY()));
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
					simon->SetScore(simon->GetScore() + 200);
					if (rand() % 2 == 1) // tỉ lệ 50%
						listItem.push_back(GetNewItem(gameObj->GetId(), gameObj->GetType(), gameObj->GetX() + 5, gameObj->GetY()));
					RunEffectHit = true;
					CountEnemyFishmen--; // giảm số lượng Fishmen đang hoạt động
					break;
				}

				default:
					break;
				}




				if (RunEffectHit)
				{
					listEffect.push_back(new Hit((int)listObj[i]->GetX() + 10, (int)listObj[i]->GetY() + 14)); // hiệu ứng hit
					listEffect.push_back(new Fire((int)gameObj->GetX() - 5, (int)gameObj->GetY() + 8)); // hiệu ứng lửa

					sound->Play(eSound::soundHit);
					switch (simon->_weaponSub->GetType())
					{
					case eType::HOLYWATER:
					{
						//HolyWater * objHolyWater = dynamic_cast<HolyWater *>(simon->_weaponSub);
						//if (objHolyWater->is==true)
						break;
					}

					case eType::DAGGER:
					{

						simon->_weaponSub->SetFinish(true); // hủy cây kiếm 
						break;
					}

					}
				}
			}
	}

	// main weapon with brick
#pragma region Object Brick
	if (simon->_weaponMain->GetFinish() == false) // Vũ khí đang hoạt động
		for (UINT i = 0; i < listObj.size(); i++)
		{
			if (listObj[i]->GetType() == eType::BRICK)
			{
				GameObject * gameObject = listObj[i];
				if (gameObject->GetHealth() > 0)
				{
					switch (gameObject->GetId())
					{

					case 39: // id 39 : brick 4 ô-> chỉ hiện effect
					{
						if (simon->_weaponMain->isCollision(listObj[i]) == true)
						{
							gameObject->SubHealth(1);
							listEffect.push_back(new Hit((int)gameObject->GetX() + 14, (int)gameObject->GetY() + 14)); // hiệu ứng hit
							listEffect.push_back(new BrokenBrick((int)gameObject->GetX() + 14, (int)gameObject->GetY() + 14, 1)); // hiệu ứng BrokenBrick
							listEffect.push_back(new BrokenBrick((int)gameObject->GetX() + 14, (int)gameObject->GetY() + 14, 2)); // hiệu ứng BrokenBrick
							listEffect.push_back(new BrokenBrick((int)gameObject->GetX() + 14, (int)gameObject->GetY() + 14, 3)); // hiệu ứng BrokenBrick
							listEffect.push_back(new BrokenBrick((int)gameObject->GetX() + 14, (int)gameObject->GetY() + 14, 4)); // hiệu ứng BrokenBrick 
							sound->Play(eSound::soundBrokenBrick);
						}
						break;
					}

					case 40: // id 40: brick 3 ô-> effect
					{
						if (simon->_weaponMain->isCollision(listObj[i]) == true)
						{
							gameObject->SubHealth(1);
							listItem.push_back(GetNewItem(gameObject->GetId(), gameObject->GetType(), gameObject->GetX(), gameObject->GetY()));
							listEffect.push_back(new Hit((int)gameObject->GetX() + 14, (int)gameObject->GetY() + 14)); // hiệu ứng hit
							listEffect.push_back(new BrokenBrick((int)gameObject->GetX() + 14, (int)gameObject->GetY() + 14, 1)); // hiệu ứng BrokenBrick
							listEffect.push_back(new BrokenBrick((int)gameObject->GetX() + 14, (int)gameObject->GetY() + 14, 2)); // hiệu ứng BrokenBrick
							listEffect.push_back(new BrokenBrick((int)gameObject->GetX() + 14, (int)gameObject->GetY() + 14, 3)); // hiệu ứng BrokenBrick
							listEffect.push_back(new BrokenBrick((int)gameObject->GetX() + 14, (int)gameObject->GetY() + 14, 4)); // hiệu ứng BrokenBrick 
							sound->Play(eSound::soundBrokenBrick);
						}
						break;
					}

					case 72: // id 72: brick -> a bonus
					{
						if (simon->_weaponMain->isCollision(listObj[i]) == true)
						{
							gameObject->SubHealth(1);
							sound->Play(eSound::soundDisplayMonney);
							listItem.push_back(GetNewItem(gameObject->GetId(), gameObject->GetType(), gameObject->GetX(), gameObject->GetY()));
							listEffect.push_back(new Hit((int)gameObject->GetX() + 14, (int)gameObject->GetY() + 14)); // hiệu ứng hit
							listEffect.push_back(new BrokenBrick((int)gameObject->GetX() + 14, (int)gameObject->GetY() + 14, 1)); // hiệu ứng BrokenBrick
							listEffect.push_back(new BrokenBrick((int)gameObject->GetX() + 14, (int)gameObject->GetY() + 14, 2)); // hiệu ứng BrokenBrick
							listEffect.push_back(new BrokenBrick((int)gameObject->GetX() + 14, (int)gameObject->GetY() + 14, 3)); // hiệu ứng BrokenBrick
							listEffect.push_back(new BrokenBrick((int)gameObject->GetX() + 14, (int)gameObject->GetY() + 14, 4)); // hiệu ứng BrokenBrick 
							sound->Play(eSound::soundBrokenBrick);

						}
						break;
					}

					case 51: // id 51: brick 2 -> effect
					{
						if (simon->_weaponMain->isCollision(listObj[i]) == true)
						{
							gameObject->SubHealth(1);
							listEffect.push_back(new Hit((int)gameObject->GetX() + 14, (int)gameObject->GetY() + 14)); // hiệu ứng hit
							listEffect.push_back(new BrokenBrick((int)gameObject->GetX() + 14, (int)gameObject->GetY() + 14, 1)); // hiệu ứng BrokenBrick
							listEffect.push_back(new BrokenBrick((int)gameObject->GetX() + 14, (int)gameObject->GetY() + 14, 2)); // hiệu ứng BrokenBrick
							listEffect.push_back(new BrokenBrick((int)gameObject->GetX() + 14, (int)gameObject->GetY() + 14, 3)); // hiệu ứng BrokenBrick
							listEffect.push_back(new BrokenBrick((int)gameObject->GetX() + 14, (int)gameObject->GetY() + 14, 4)); // hiệu ứng BrokenBrick 
							sound->Play(eSound::soundBrokenBrick);

						}
						break;
					}

					}
				}



			}
		}

#pragma endregion


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
					simon->_weaponSub = new Dagger();
					listItem[i]->SetFinish(true);
					sound->Play(eSound::soundCollectWeapon);
					break;
				}

				case eType::ITEMHOLYWATER:
				{
					SAFE_DELETE(simon->_weaponSub);
					simon->_weaponSub = new HolyWater();
					listItem[i]->SetFinish(true);
					sound->Play(eSound::soundCollectWeapon);
					break;
				}

				case eType::BONUS:
				{
					listItem[i]->SetFinish(true);
					sound->Play(eSound::soundCollectItem);
					simon->SetScore(1000);
					break;
				}


				case eType::POTROAST:
				{
					listItem[i]->SetFinish(true);
					sound->Play(eSound::soundCollectItem);
					simon->SetHealth(min(simon->GetHealth() + 6, 16)); // tăng 6 đơn vị máu
					break;
				}

				case eType::STOPWATCH:
				{
					SAFE_DELETE(simon->_weaponSub);
					simon->_weaponSub = new StopWatch();
					listItem[i]->SetFinish(true);
					sound->Play(eSound::soundCollectWeapon);
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
#pragma region Object Hidden
	for (UINT i = 0; i < listObj.size(); i++)
	{
		if (listObj[i]->GetType() == eType::OBJECT_HIDDEN)
		{
			GameObject * gameObject = listObj[i];

			if (gameObject->GetHealth() > 0)
			{
				//LPCOLLISIONEVENT e = simon->SweptAABBEx(listObj[i]); 
				//if (0.0f < e->t && e->t <= 1.0f) // có va chạm xảy ra
				if (simon->isCollitionObjectWithObject(gameObject)) // có va chạm xảy ra
				{
					switch (gameObject->GetId())
					{
					case 67: // đụng trúng box xác nhận simon đã qua cửa
					{
						if (isProcessingGoThroughTheDoor1)
						{
							isDoneSimonGoThroughTheDoor1 = true;
							camera->SetAutoGoX(abs(ViTriCameraDiChuyenSauKhiQuaCua - camera->GetXCam()), SIMON_WALKING_SPEED);
							isDoneCameraGoThroughTheDoor1 = false;
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

					case 41: // id 41: object ẩn -> xuống hồ nước
					{
						camera->SetPosition(camera->GetXCam(), CAMERA_POSITION_Y_LAKE);
						camera->SetBoundary(CAMERA_BOUNDARY_LAKE_LEFT, CAMERA_BOUNDARY_LAKE_RIGHT);
						simon->SetPosition(3150, 405);
						isAllowCreateBat = false;  // không cho tạo Bat
						isAllowCreateFishmen = true;
						break;
					}
					case 45: // id 45: object ẩn -> trở lên trước khi xuống hồ nước
					{
						camera->SetPosition(camera->GetXCam(), 0);
						simon->SetPosition(3152, 345);
						isAllowCreateBat = true;  // không cho tạo Bat
						isAllowCreateFishmen = false;
						TimeWaitCreateBat = 3000 + rand() % 1000;
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


					}
					
				}
			}
		}
	}

#pragma endregion

}

void Scene_2::CheckCollisionWithEnemy()
{
	CheckCollisionWeapon(listEnemy); // enemy bt
	CheckCollisionSimonWithEnemy();
}

void Scene_2::CheckCollisionSimonWithEnemy()
{
	if (GetTickCount() - simon->untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		simon->untouchable_start = 0;
		simon->untouchable = false;
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
				if (e->t > 0 && e->t <= 1) // có va chạm
				{
					simon->SetHurt(e);
					return; // giảm chi phí duyệt, vì nếu có va chạm thì cũng đang untouchable
				}

				if (simon->checkAABB(gameobj) == true)
				{
					LPCOLLISIONEVENT e = new CollisionEvent(1, -simon->GetDirection(), 0, NULL);
					simon->SetHurt(e);
					return; // giảm chi phí duyệt, vì nếu có va chạm thì cũng đang untouchable
				}

			}
		}
#pragma endregion
	 
	}



}

void Scene_2::CheckCollisionSimonWithGate()
{
	for (UINT i = 0; i < listObj.size(); i++)
	{
		if (listObj[i]->GetType() == eType::GATE)
		{
			if (simon->isCollitionObjectWithObject(listObj[i]))
			{
				Gate* objGate = dynamic_cast<Gate*>(listObj[i]);
				if (objGate->GetId() == 64) // id object
				{
					if (objGate->GetStart() == 0)
					{
						//di chuyển camera đến ViTriCameraDiChuyenTruocKhiQuaCua = 2825.0f
						camera->SetBoundary(camera->GetBoundaryLeft(), camera->GetBoundaryRight() + 1064+100);// mở biên phải rộng ra thêm để chạy AutoGo
						camera->SetAutoGoX(abs(ViTriCameraDiChuyenTruocKhiQuaCua - camera->GetXCam()), SIMON_WALKING_SPEED);
						
						//simon->Stop();
#pragma region Stop simon
						simon->SetSpeed(0, simon->GetVy()); // cho simon dừng, tránh trường hợp không vào được trạng thái stop trong KeyState()
						simon->isWalking = 0;
						if (simon->isSitting == true) // nếu simon đang ngồi
						{
							simon->isSitting = 0; // hủy trạng thái ngồi
							simon->SetY(simon->GetY() - 18); // kéo simon lên
						}
#pragma endregion

						

						isProcessingGoThroughTheDoor1 = true; // bật trạng thái xử lí qua cửa
						isDoneSimonGoThroughTheDoor1 = false;
						objGate->Start();

						DebugOut(L"Simon dung trung cua!\n");


						break;
					}

				}

			}
		}
	}
}



Item * Scene_2::GetNewItem(int Id, eType Type, float X, float Y)
{
	if (Type == eType::CANDLE)
	{
		switch (Id)
		{
		case 40:
			return new ItemHolyWater(X, Y);
			break;

		case 71:
			return new ItemHolyWater(X, Y);
			break;

		default:
			return new SmallHeart(X, Y);
			break;
		}

	}


	if (Type == eType::GHOST || Type == eType::PANTHER || Type == eType::BAT)
	{
		int random = rand() % 10;

		while (simon->_weaponMain->GetLevel() == 2 && random == 4)
		{
			random = rand() % 10;
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

		default:
			return new SmallHeart(X, Y);
			break;
		}

	}


	if (Type == eType::OBJECT_HIDDEN)
	{
		if (Id == 65)
			return new Bonus(3763.0f,587.0f);

	}

	return new LargeHeart(X, Y);
}