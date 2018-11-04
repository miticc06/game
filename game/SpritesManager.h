#ifndef __SpritesManager_H__
#define __SpritesManager_H__

#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "define.h"

#include "Game.h"
#include "debug.h"
#include <string>
#include "Sprite.h"

#include <fstream>
#include <iostream>
/*
	Manage sprite database
*/
class SpritesManager
{
	static SpritesManager * __instance;
	map<eID, Sprite*> _listSprite; // chứa texture
	map<eID, map<string, RECT>> _sourceRectList;

public:
	//void Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	//LPSPRITE Get(int id);

	static SpritesManager * GetInstance();

	Sprite* getSprite(eID id);
	RECT getSourceRect(eID id, string rectName); // get các RECT từ file
	void loadSpriteInfo(eID id, string fileInfoPath); // đọc các RECT từ file

	void loadResource();

};


#endif