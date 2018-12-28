#ifndef __HIT_H__
#define __HIT_H__

#include <d3dx9.h>
#include "GSprite.h"
#include "Effect.h"

class Hit :	public Effect
{
public:
	Hit(float X = 0, float Y = 0);
	~Hit();

	void Update(DWORD dt);
};

#endif
 
#ifndef HIT_ADD_EFFECT
#define HIT_ADD_EFFECT(listEffect, gameObject) \
listEffect.push_back(new Hit(gameObject->GetX() + 14, gameObject->GetY() + 14));\

#endif
