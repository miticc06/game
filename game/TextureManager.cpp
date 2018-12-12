#include "TextureManager.h"

TextureManager* TextureManager::__Instance = NULL;

TextureManager * TextureManager::GetInstance()
{
	if (__Instance == NULL)
		__Instance = new TextureManager();
	return __Instance;
}

void TextureManager::AddTexture(eType type, GTexture *texture)
{
	_ArrTextures[type] = texture;
}

GTexture * TextureManager::GetTexture(eType type)
{
	return _ArrTextures[type];
}

void TextureManager::LoadResource()
{
	// Intro
	AddTexture(eType::MAINMENU, new GTexture("Resources/mainmenu.png"));
	AddTexture(eType::INTRO_BAT, new GTexture("Resources/intro_bat.png", 2, 1, 2));
	AddTexture(eType::INTRO_BAT_MENU, new GTexture("Resources/IntroBatMenu.png",5,3,15));
	AddTexture(eType::INTRO_GO_SCENE1, new GTexture("Resources/intro_go_scene_1.png"));
	AddTexture(eType::HELICOPTER, new GTexture("Resources/helicopter.png"));

	//board
	AddTexture(eType::FONT, new GTexture("Resources/font/1.png", 13, 3, 37));

	AddTexture(eType::BOARD, new GTexture("Resources/blackboard.png", 1, 1, 1));
	AddTexture(eType::BOARD_TRANS, new GTexture("Resources/blackboard.png",1,1,1,0,0,0));
	
	AddTexture(eType::BOARDHEALTH, new GTexture("Resources/heal.png", 3, 1, 3));
	AddTexture(eType::RENDERBBOX, new GTexture("textures/bbox.png")); // dùng để vẽ BBOX

	//MAP
	AddTexture(eType::MAP1, new GTexture("Resources/map/1.png", 8, 4, 32));
	//AddTexture(eType::MAP2, new GTexture("Resources/map/2.png", 18, 4, 72));
	AddTexture(eType::MAP2, new GTexture("Resources/map/2.png", 22, 4, 88));


	//gameobject ground
	AddTexture(eType::TEX_BRICK_MODEL_1, new GTexture("Resources/ground/2.png")); // loại dành cho state 1
	AddTexture(eType::TEX_BRICK_MODEL_2, new GTexture("Resources/ground/2-2.png")); // dành cho state 2
	AddTexture(eType::TEX_BRICK_MODEL_3, new GTexture("Resources/ground/8.png")); // loại nhỏ
	AddTexture(eType::TEX_BRICK_TRANSPARENT, new GTexture("Resources/ground/brick_transparent.png")); // loại trong suốt
	
	AddTexture(eType::TEX_BRICK_MODEL_3_3_32, new GTexture("Resources/ground/8-2.png")); // loại nhỏ 4 ô
	AddTexture(eType::TEX_BRICK_MODEL_3_4_32, new GTexture("Resources/ground/8-1.png")); // loại nhỏ 4 ô



	 

	AddTexture(eType::GATE, new GTexture("Resources/ground/Gate1.png", 4,1,4));

	AddTexture(eType::TORCH, new GTexture("Resources/ground/0.png", 2, 1, 2));
	AddTexture(eType::CANDLE, new GTexture("Resources/ground/1.png", 2, 1, 2));

	//item
	AddTexture(eType::ITEMDAGGER, new GTexture("Resources/item/4.png"));
	AddTexture(eType::LARGEHEART, new GTexture("Resources/item/1.png"));
	AddTexture(eType::UPGRADEMORNINGSTAR, new GTexture("Resources/item/3.png"));
	AddTexture(eType::BONUS, new GTexture("Resources/item/2.png", 3,1,3));
	AddTexture(eType::SMALLHEART, new GTexture("Resources/item/0.png"));
	AddTexture(eType::ITEMHOLYWATER, new GTexture("Resources/item/9.png"));
	AddTexture(eType::POTROAST, new GTexture("Resources/item/10.png"));
	AddTexture(eType::CRYSTALBALL, new GTexture("Resources/item/13.png",2,1,2));
	AddTexture(eType::ITEMTHROWINGAXE, new GTexture("Resources/item/7.png"));
	AddTexture(eType::INVISIBILITYPOTION, new GTexture("Resources/item/14.png"));
	AddTexture(eType::CROSS, new GTexture("Resources/item/6.png"));




	// Weapon
	AddTexture(eType::DAGGER, new GTexture("Resources/weapon/1.png"));
	AddTexture(eType::MORNINGSTAR, new GTexture("Resources/weapon/morningstar.png", 4, 3, 12));
	AddTexture(eType::HOLYWATER, new GTexture("Resources/weapon/2.png", 4,1, 4));
	AddTexture(eType::STOPWATCH, new GTexture("Resources/item/5.png"));
	AddTexture(eType::FIREBALL, new GTexture("Resources/weapon/fireball.png"));
	AddTexture(eType::THROWINGAXE, new GTexture("Resources/weapon/3.png",4,1,4));


	//player
	AddTexture(eType::SIMON, new GTexture("Resources/simon.png", 8, 3, 24));
	AddTexture(eType::SIMON_TRANS, new GTexture("Resources/simon_trans.png", 8, 3, 24));
	AddTexture(eType::SIMON_DEADTH, new GTexture("Resources/simondeath.png"));

	//effect
	AddTexture(eType::FIRE, new GTexture("Resources/other/1.png", 4, 1, 4));
	AddTexture(eType::HIT, new GTexture("Resources/other/0.png", 2,1,2));
	AddTexture(eType::BROKENBRICK, new GTexture("Resources/other/BrokenBrick.png", 4,4,16));
	AddTexture(eType::STEAM, new GTexture("Resources/other/2.png"));



	//enemy
	AddTexture(eType::GHOST, new GTexture("Resources/enemy/1.png", 2, 1, 2));
	AddTexture(eType::PANTHER, new GTexture("Resources/enemy/2.png", 4, 1, 4));

	
	AddTexture(eType::BAT, new GTexture("Resources/enemy/0.png", 4, 1, 4));
	AddTexture(eType::FISHMEN, new GTexture("Resources/enemy/3.png", 3, 1, 3));
	
	
	//boss
	AddTexture(eType::PHANTOMBAT, new GTexture("Resources/boss/0.png", 3, 1, 3));



}





TextureManager::TextureManager()
{
	LoadResource();// load đúng 1 lần
}


TextureManager::~TextureManager()
{
}
