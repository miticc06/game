#include "SpritesManager.h"
 
SpritesManager * SpritesManager::__instance = NULL;

SpritesManager *SpritesManager::GetInstance()
{
	if (__instance == NULL)
		__instance = new SpritesManager();
	return __instance;
}


Sprite* SpritesManager::getSprite(eID id)
{
	Sprite* it = this->_listSprite.find(id)->second;
	return new Sprite(*it); // cần xem lại ngay đây
}

RECT SpritesManager::getSourceRect(eID id, string rectName)
{
	return _sourceRectList[id][rectName];
}

void SpritesManager::loadSpriteInfo(eID id, string fileInfoPath)
{

	ifstream fileIn;
	fileIn.open(fileInfoPath, ios::in);

	if (fileIn)
	{
		// Đọc dòng đầu tiên của file (title)
		string firstLine;
		getline(fileIn, firstLine);

		while (!fileIn.eof())
		{
			string rectName;
			RECT frameRect;
			fileIn >> rectName >> frameRect.left >> frameRect.top >> frameRect.right >> frameRect.bottom;
			_sourceRectList[id][rectName] = frameRect;
		}
		fileIn.close();
	}
}

void SpritesManager::loadResource()
{

	Sprite* _sprite = nullptr;
	_sprite = new Sprite(L"textures\\mario.png", D3DCOLOR_XRGB(255, 255, 255));
	this->_listSprite[eID::MARIO] = _sprite;
	this->loadSpriteInfo(eID::MARIO, "textures\\mario.txt");

	_sprite = new Sprite(L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255)); // special texture to draw object bounding box
	this->_listSprite[eID::BBOX] = _sprite;

}
