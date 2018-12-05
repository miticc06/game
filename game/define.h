#ifndef _DEFINE_H__
#define _DEFINE_H__

#define _USE_MATH_DEFINES

#include <d3d9.h>
#include <d3dx9.h>
#include <map>
#include "debug.h"

#include <vector>

#include <Windows.h> 

#include <string>


#include <algorithm>


#include <stdio.h>

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <iostream>
#include <iomanip>



using namespace std;
 

#define COLOR_BLACK D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)  
#define COLOR_KEY D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f) 


#define SHOWBOX_PINK 0




#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 480 //512//448


#define IS_DEBUG_RENDER_BBOX 1

#define MAX_FRAME_RATE 90
//#define DT_DEFAULT dt//1000/MAX_FRAME_RATE
 
extern int Window_Width; 
extern int Window_Height;
// kích thước màn hình

extern int MapWidth;
extern int MapHeight;


extern int ScreenColumn;
extern int ScreenRow;


extern int isDebug_Untouchable;


// ID của Sprite, object
enum eType
{
	SIMON = 01,


	// object nền
	BRICK = 21,
	TEX_BRICK_MODEL_1 = 22,
	TEX_BRICK_MODEL_2 = 23,
	TEX_BRICK_MODEL_3 = 24,
	TEX_BRICK_TRANSPARENT = 25,
	GATE = 26,
	TEX_BRICK_MODEL_3_3_32 = 27,
	TEX_BRICK_MODEL_3_4_32 = 28,

	// object
	TORCH = 41,
	OBJECT_HIDDEN = 42,
	CANDLE = 43,
	STAIR = 44,
/*	STAIR_UP = 45,
	STAIR_EXIT = 46,*/
	STAIR_BOTTOM = 47,
	STAIR_TOP = 48,



	// weapon
	MORNINGSTAR = 61,
	DAGGER = 62,
	HOLYWATER = 63,
	STOPWATCH = 64,
	FIREBALL = 65,

	// item
	LARGEHEART = 81,
	UPGRADEMORNINGSTAR = 82,
	ITEMDAGGER = 83,
	BONUS = 84,
	SMALLHEART = 85,
	ITEMHOLYWATER =86,
	POTROAST = 87,

	// other
	FONT = 101,
	BOARD = 102,
	BOARDHEALTH = 103,
	MAP1 = 104,
	RENDERBBOX =105,
	MAP2 = 106,


	// Effect
	FIRE = 121,
	HIT = 122,
	BROKENBRICK = 123,
	STEAM = 124,
	
	// Enemy
	GHOST = 141,
	PANTHER = 142,
	BAT = 143,
	FISHMEN = 144
};



 
 
enum eDirection
{
	NONE = 0,
	TOP = (1 << 0),
	LEFT = (1 << 1),
	RIGHT = (1 << 2),
	BOTTOM = (1 << 3)
};
 
 

typedef D3DXVECTOR3 GVector3;
typedef D3DXVECTOR2 GVector2;
#define VECTOR2ZERO GVector2(0.0f, 0.0f)












#ifndef SAFE_DELETE

#define SAFE_DELETE(ptr) \
if(ptr) \
{\
	delete (ptr); \
	ptr = nullptr; \
} \

#endif

#endif 