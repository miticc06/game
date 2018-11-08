#ifndef __CTEXTURE_H__
#define __CTEXTURE_H__
 
#include "Game.h"
#include "define.h"

class GTexture 
{
public:
	char* FileName; //đường dẫn tới file ảnh
	RECT Size;		//độ phân giải ảnh
	LPDIRECT3DTEXTURE9 Texture;
	int Cols;		//số cột frame
	int Rows;		//số hàng frame
	int Count;		//tổng số frame
	int FrameWidth;		//width of 1 frame
	int FrameHeight;	//height of 1 frame

	GTexture(char* _fileName, int cols = 1, int rows = 1, int count = 1, int Showbox = 0);
	GTexture(char* _fileName, int cols, int rows, int count, int R, int G, int B);
	~GTexture();
	//vẽ texture tại vị trí (x, y) trên màn hình
	void Draw(int x, int y);

protected:
	void Load(int ShowBox);
	void Load(int R, int G, int B);
};

#endif