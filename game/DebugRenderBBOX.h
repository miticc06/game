#ifndef __DEBUGRENDERBBOX_H__
#define __DEBUGRENDERBBOX_H__


#include "define.h"
#include "GTexture.h"


class DebugRenderBBOX
{
private:
	GTexture * _gTextureBBOX;

public:
	static DebugRenderBBOX * __instance;
	static DebugRenderBBOX * GetInstance();
	DebugRenderBBOX();
	~DebugRenderBBOX();
	LPDIRECT3DTEXTURE9 GetTexture();
};



#endif // !__DEBUGRENDERBBOX_H__

