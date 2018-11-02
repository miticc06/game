#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>

using namespace std;

class Sprite
{
	int id;				// Sprite ID in the sprite database

	int left; 
	int top;
	int right;
	int bottom;

	LPDIRECT3DTEXTURE9 texture;
public: 
	Sprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);

	void Draw(float x, float y, int alpha = 255);
};

typedef Sprite * LPSPRITE;

/*
	Manage sprite database
*/
class Sprites
{
	static Sprites * __instance;

	unordered_map<int, LPSPRITE> sprites;

public:
	void Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(int id);

	static Sprites * GetInstance();
};

/*
	Sprite animation
*/
class AnimationFrame
{
	LPSPRITE sprite;
	DWORD time;

public:
	AnimationFrame(LPSPRITE sprite, int time)
	{ 
		this->sprite = sprite; 
		this->time = time;
	}

	DWORD GetTime() 
	{ 
		return time; 
	}
	LPSPRITE GetSprite() { return sprite; }
};

typedef AnimationFrame *LPANIMATION_FRAME;

class Animation
{
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
public:
	Animation(int defaultTime) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(int spriteId, DWORD time = 0);
	void Render(float x, float y, int alpha=255);
};

 
class Animations
{
	static Animations * __instance;

	unordered_map<int, Animation *> animations;

public:
	void Add(int id, Animation * ani);
	Animation * Get(int id);

	static Animations * GetInstance();
};

