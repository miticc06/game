

#include "Scene_Intro.h"



Scene_Intro::Scene_Intro()
{
	LoadResources();
}


Scene_Intro::~Scene_Intro()
{
	SAFE_DELETE(simon);
	SAFE_DELETE(board);
}

void Scene_Intro::KeyState(BYTE * state)
{
}

void Scene_Intro::OnKeyDown(int KeyCode)
{
	if (KeyCode == DIK_2) // lấy tọa độ world của chuột 
	{
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(Game::GetInstance()->GetWindowHandle(), &p);
		DebugOut(L"[MOUSE POSITION] %d %d \n", p.x, p.y);
	}
	else
	{
		isPressStart = true; // nhấn phím bất kì thì xác nhận đã nhấn
	}
}

void Scene_Intro::OnKeyUp(int KeyCode)
{
}

void Scene_Intro::LoadResources()
{
	TextureManager * _textureManager = TextureManager::GetInstance(); // Đã gọi load resource
	sound = Sound::GetInstance();

	Sprite_MainMenu = new GSprite(_textureManager->GetTexture(eType::MAINMENU), 0);
	Sprite_IntroBatMenu = new GSprite(_textureManager->GetTexture(eType::INTRO_BAT_MENU), 100); 

	StatusProcess = INTRO_STATUS_PROCESS_MENU;
	TimeWaited = 0;
	isPressStart = 0;

	isDrawTextPressStart = true; 

	simon = new Simon();
	board = new Board(BOARD_DEFAULT_POSITION_X, BOARD_DEFAULT_POSITION_Y);
	Sprite_IntroGoScene1 = new GSprite(_textureManager->GetTexture(eType::INTRO_GO_SCENE1), 0);

	heliCopter = new HeliCopter(432, 146);
	introBat1 = new IntroBat(297, 129, -0.01, 0.0f); // Đi ngang qua trái
	introBat2 = new IntroBat(47,224, 0.02, -0.01f); // Đi góc dưới trái lên phải trên

	//297 129
} 
void Scene_Intro::Update(DWORD dt)
{
	switch (StatusProcess)
	{
	case INTRO_STATUS_PROCESS_MENU:
	{
		if (!isPressStart) // chưa nhấn phím thì update sprite
			Sprite_IntroBatMenu->Update(dt);

		if (isPressStart)
		{
			TimeWaited += dt;
			if (TimeWaited >= 1000)
			{ // qua trạng thái 2
				StatusProcess = INTRO_STATUS_PROCESS_GO_SCENE1;
				sound->Play(eSound::musicGame_Start_Prologue);
				camera = SceneManager::GetInstance()->GetCamera();
				camera->SetPosition(0, 0);
				listBrick.push_back(new Brick(0, 400, 600, 32, BRICK_MODEL_TRANSPARENT));
				simon->SetPosition(500, 336);
				simon->SetDirection(-1);
				 
				simon->SetAutoGoX(-1, -1, abs(225 - simon->GetX()), SIMON_WALKING_SPEED);
			}
			else
			{
				TimeWaitedToChangeDisplayTextPressStart += dt;
				if (TimeWaitedToChangeDisplayTextPressStart >= 150)
				{
					TimeWaitedToChangeDisplayTextPressStart = 0;
					isDrawTextPressStart = !isDrawTextPressStart; // lật trạng thái
				}
			}
		}

		break;
	}

	case INTRO_STATUS_PROCESS_GO_SCENE1:
	{ 
		if (simon->GetIsAutoGoX())
		{
			simon->Update(dt, camera, &listBrick);
		}
		else
		{
			simon->GetSprite()->SelectIndex(SIMON_ANI_HIDE_FACE);
		}

		heliCopter->Update(dt);

		introBat1->Update(dt);
		introBat2->Update(dt);

		if (sound->isPlaying(eSound::musicGame_Start_Prologue) == false)
		{
			SceneManager::GetInstance()->SetScene(new Scene_1());
		}

		break;
	}
	}
	
}

void Scene_Intro::Render()
{
	switch (StatusProcess)
	{
	case INTRO_STATUS_PROCESS_MENU:
	{
		Sprite_MainMenu->Draw(0, -3); // vẽ nền
		Sprite_IntroBatMenu->Draw(345, 195); // vẽ nền
		if (isDrawTextPressStart)
			TextPressStart.Draw(160, 270, "PUSH START KEY");
		break;
	}

	case INTRO_STATUS_PROCESS_GO_SCENE1:
	{
		
		Sprite_IntroGoScene1->Draw(0, 0);
		
		heliCopter->Render(camera);

		introBat1->Render(camera);
		introBat2->Render(camera);

 		board->Render(simon, 1, NULL, 300, NULL);
		simon->Render(camera);

		

		break;
	} 
	}
	
}
