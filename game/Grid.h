#ifndef __GRID_H__
#define	__GRID_H__


#include "Game.h" 
#include "GSprite.h" 
#include "Map.h"
#include "Torch.h"
#include "Brick.h"
#include "define.h"
#include "ObjectHidden.h"
#include "Candle.h"
#include "Stair.h"
#include "ExitStair.h"
#include "StairTop.h"
#include "StairBottom.h"


using namespace std;

#define GRID_CELL_WIDTH 256
#define GRID_CELL_HEIGHT 224
#define GRID_BASE 10



class Grid
{ 

private:
	vector<GameObject*> listObjectGame;
	vector<GameObject*> cells[500][500];

	void ResetTake();
 
public:
	void ReadFileToGrid(char * filename); // Đọc các object từ file
	void GetListObject(vector<Object*>& ListObj, Camera * camera);
	void GetListObject(vector<Object*> &ListObj, GameObject * obj);


	void Insert(int id, int type, int trend, int x, int y, int w, int h, int Model); //Thêm object vào grid

	GameObject * GetNewObject(int type, int x, int y, int w, int h, int Model);

	Grid();
	~Grid();
};

#endif