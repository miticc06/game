#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__

#include <unordered_map>
#include "define.h"
#include "GTexture.h"
class TextureManager
{
	unordered_map<eID, GTexture*> _ArrTextures;
	
public:
	static TextureManager* __Instance;
	static TextureManager* GetInstance();

	void AddTexture(eID type, GTexture* texture);
	GTexture* GetTexture(eID type);

	void LoadResource();

	TextureManager();
	~TextureManager();
};

#endif