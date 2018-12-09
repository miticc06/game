

#include "Scene_Intro.h"



Scene_Intro::Scene_Intro()
{
	LoadResources();
}


Scene_Intro::~Scene_Intro()
{
}

void Scene_Intro::KeyState(BYTE * state)
{
}

void Scene_Intro::OnKeyDown(int KeyCode)
{
	isPressStart = true; // nhấn phím bất kì thì xác nhận đã nhấn
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
			{
				StatusProcess = INTRO_STATUS_PROCESS_GO_SCENE1;
				// qua trangj thai 2
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

		break;
	} 
	}
	
}
