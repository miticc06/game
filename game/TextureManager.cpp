﻿#include "TextureManager.h"

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
	//board
	AddTexture(eType::FONT, new GTexture("Resources/font/1.png", 13, 3, 37, 0));
	AddTexture(eType::BOARD, new GTexture("Resources/blackboard.png"));
	AddTexture(eType::BOARDHEALTH, new GTexture("Resources/heal.png", 3, 1, 3));
	AddTexture(eType::RENDERBBOX, new GTexture("textures/bbox.png")); // dùng để vẽ BBOX

	//MAP
	AddTexture(eType::MAP1, new GTexture("Resources/map/1.png", 10, 4, 40));
	//AddTexture(eType::MAP2, new GTexture("Resources/map/2.png", 18, 4, 72));
	AddTexture(eType::MAP2, new GTexture("Resources/map/2.png", 18, 5, 90));


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




	// Weapon
	AddTexture(eType::DAGGER, new GTexture("Resources/weapon/1.png"));
	AddTexture(eType::MORNINGSTAR, new GTexture("Resources/weapon/morningstar.png", 4, 3, 12));
	AddTexture(eType::HOLYWATER, new GTexture("Resources/weapon/2.png", 4,1, 4));
	AddTexture(eType::STOPWATCH, new GTexture("Resources/item/5.png"));
	AddTexture(eType::FIREBALL, new GTexture("Resources/weapon/fireball.png"));


	//player
	AddTexture(eType::SIMON, new GTexture("Resources/simon.png", 8, 3, 24));

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




}





TextureManager::TextureManager()
{
	LoadResource();// load đúng 1 lần
}


TextureManager::~TextureManager()
{
}
