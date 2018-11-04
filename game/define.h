#ifndef _DEFINE_H__
#define _DEFINE_H__

#define _USE_MATH_DEFINES

#include <d3d9.h>
#include <d3dx9.h>
#include <map> 
using namespace std;

#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 448

#define COLOR_BLACK D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)  
#define COLOR_KEY D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f) 

// ID của Sprite, object
enum eID
{
	MARIO,
	BBOX
};

 enum eStatus
{
	NORMAL = 0,
	MOVING_LEFT = (1 << 0),		//00000001
	MOVING_RIGHT = (1 << 1),	//00000010
	JUMPING = (1 << 2),			//00000100
	FALLING = (1 << 3),			//00001000
	RUNNING = (1 << 4),			//00010000
	LOOKING_UP = (1 << 5),
	ROLLING_DOWN = (1 << 6),
	ATTACKING = (1 << 7),
	DIE = (1 << 8),
	DESTROY = (1 << 9)
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

#endif // !SAFE_DELETE

#endif // !_DEFINE_H__
