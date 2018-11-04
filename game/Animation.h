#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "define.h"

#include "Game.h"
#include "debug.h"
#include <string>
#include <fstream>
#include <iostream>
#include "SpritesManager.h"


#include "Sprite.h"

using namespace std;

class Animation // trong Animation này sẽ chứa nhiều frames - AnimationFrames
{

private:
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<RECT> _frameRectList;
	Sprite *  _sprite;
public:
	Animation(); 

	Animation(Sprite* sprite, int defaultTime);
	 
	void Render(float x, float y, int alpha = 255);


	void addFrameRect(eID id, char* firstRectName, ...);
	void addFrameRect(RECT rect);


};


#endif