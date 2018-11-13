#ifndef __EFFECT_H__
#define __EFFECT_H__

#include "GSprite.h"
#include "GTexture.h"
#include "TextureManager.h"
#include "Camera.h"



class Effect
{
protected:
	GTexture * _texture;
	GSprite * _sprite;

	int x;
	int y;
	bool isFinish;

public:
	Effect();
	virtual ~Effect();

	virtual void Render(Camera * camera);
	virtual void Update(DWORD dt);
	bool GetFinish();
	void SetFinish(int b);
};



#endif 