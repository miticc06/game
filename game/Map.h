#ifndef __MAP_H__
#define __MAP_H__

#include "define.h"
#include "GTexture.h"
#include "GSprite.h"

#include "Camera.h"
#include "TextureManager.h"
 
class Map
{
private:
	GTexture *_texture;
	GSprite *_sprite;
	 
	int NumColumnTile;
	int NumRowTile;

	int RowMatrix; 
	int ColumnMatrix;
	 
	int TotalTiles;


	int HeightBoard; // chiều cao board
	 
	int TileMap[500][500];

public:
	Map();
	~Map();
	void LoadMap(eType type);
	void ReadMapTXT(char * filename);
	void DrawMap(Camera * camera);

	int GetMapWidth();
	int GetMapHeight();
};




#endif