#ifndef __HIT_H__
#define __HIT_H__

#include <d3dx9.h>
#include "GSprite.h"
#include "Effect.h"

class Hit :	public Effect
{
public:
	Hit(int X = 0, int Y = 0);
	~Hit();

	void Update(DWORD dt);
};

#endif
 