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


#define SHOWBOX_PINK 0




#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 448

 
 

extern int Window_Width;
extern int Window_Height;

extern int MapWidth;
extern int MapHeight;


extern int ScreenColumn;
extern int ScreenRow;


// ID của Sprite, object
enum eID
{
	SIMON = 01,


	BRICK = 21
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



//
//void GLTrace(char* format, ...)
//{
//	char *_traceFile = "C:\\Temp\\Sample_TH_game.log";
//	int _traceNum = 1;
//
//	if (!_traceNum) return;
//
//	FILE *f = stderr;
//	if (_traceFile != NULL)
//	{
//		if (fopen_s(&f, _traceFile, "a") != 0)
//		{
//			fprintf(stderr, "WARNING: Failed to open trace file '%s' for writing!\n", _traceFile);
//			return;
//		}
//	}
//	va_list ap;
//	va_start(ap, format);
//	fprintf(f, format, ap);
//	va_end(ap);
//	fprintf(f, "\n");
//	if (_traceFile != NULL) fclose(f);
//}
//
//void GLMessage(char* text)
//{
//	//	Game::GetInstance()->
//		//MessageBoxA(G_hWnd, text, "Sample TH", MB_OK);
//}
//
//void GLTitle(char* text) {
//	//SetWindowTextA(G_hWnd, text);
//}
//
//void OutDebug(const char * text)
//{
//	OutputDebugStringA(text);
//	OutputDebugStringA("\n");
//
//}
//








#ifndef SAFE_DELETE

#define SAFE_DELETE(ptr) \
if(ptr) \
{\
	delete (ptr); \
	ptr = nullptr; \
} \

#endif // !SAFE_DELETE

#endif // !_DEFINE_H__
