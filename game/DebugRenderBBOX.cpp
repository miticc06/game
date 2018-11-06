#include "DebugRenderBBOX.h"

DebugRenderBBOX * DebugRenderBBOX::__instance = NULL;


DebugRenderBBOX * DebugRenderBBOX::GetInstance()
{
	if (__instance == NULL)
		__instance = new DebugRenderBBOX();
	return __instance;
}

DebugRenderBBOX::DebugRenderBBOX()
{
	_gTextureBBOX= new GTexture("textures\\bbox.png");
}


DebugRenderBBOX::~DebugRenderBBOX()
{
	SAFE_DELETE(__instance);

}

LPDIRECT3DTEXTURE9 DebugRenderBBOX::GetTexture()
{
	return _gTextureBBOX->Texture;
}
