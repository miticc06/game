#include "Sprites.h"
#include "Game.h"
#include "debug.h"

Sprite::Sprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
}

SpritesManager * SpritesManager::__instance = NULL;

SpritesManager *SpritesManager::GetInstance()
{
	if (__instance == NULL) 
		__instance = new SpritesManager();
	return __instance;
}

void Sprite::Draw(float x, float y, int alpha)
{
	Game * game = Game::GetInstance();
	game->Draw(x, y, texture, left, top, right, bottom, alpha);
}

void SpritesManager::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new Sprite(id, left, top, right, bottom, tex);
	sprites[id] = s;
}

LPSPRITE SpritesManager::Get(int id)
{
	return sprites[id];
}



void Animation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0)
		t = this->defaultTime;

	LPSPRITE sprite = SpritesManager::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new AnimationFrame(sprite, t);
	frames.push_back(frame);
}

void Animation::Render(float x, float y, int alpha)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1) 
	{
		currentFrame = 0; 
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
		}
		
	}

	frames[currentFrame]->GetSprite()->Draw(x, y, alpha);
}

AnimationsManager * AnimationsManager::__instance = NULL;

AnimationsManager * AnimationsManager::GetInstance()
{
	if (__instance == NULL) __instance = new AnimationsManager();
	return __instance;
}

void AnimationsManager::Add(int id, Animation * ani)
{
	animations[id] = ani;
}

Animation * AnimationsManager::Get(int id)
{
	return animations[id];
}