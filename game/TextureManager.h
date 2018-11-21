#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__

#include <unordered_map>
#include "define.h"
#include "GTexture.h"
class TextureManager
{
	unordered_map<eType, GTexture*> _ArrTextures;
	
public:
	static TextureManager* __Instance;
	static TextureManager* GetInstance();

	void AddTexture(eType type, GTexture* texture);
	GTexture* GetTexture(eType type);

	void LoadResource();

	TextureManager();
	~TextureManager();
};

#endif