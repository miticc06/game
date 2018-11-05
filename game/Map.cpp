#include "Map.h"



Map::Map()
{
	LoadMap();
}


Map::~Map()
{
}

void Map::LoadMap()
{
	ReadMapTXT("Resources/map/1.txt");
	TileTexture = new GTexture("Resources/map/1.png", ColTile, RowTile, CountTileFrame);
	TileSprite = new GSprite(TileTexture, 0);
}

void Map::ReadMapTXT(char * filename)
{ 
	ifstream fileIn;
	fileIn.open(filename, ios::in);

	if (fileIn)
	{
		fileIn >> RowMatrix >> ColumnMatrix >> ColTile >> RowTile >> CountTileFrame;
 		for (int i = 0; i < RowMatrix; i++)
		{
			for (int j = 0; j < ColumnMatrix; j++)
			{
				fileIn >> TileMap[i][j]; 
			}
		}
		fileIn.close(); 
	} 


}

void Map::DrawMap()
{
	for (int i = 0; i < (SCREEN_HEIGHT / TILE_FRAME_HEIGHT); i++)
	{
		for (int j = 0; j < (SCREEN_WIDTH / TILE_FRAME_WIDTH); j++)
		{
			TileSprite->SelectIndex(TileMap[i][j]);
			TileSprite->Draw(0 + j * TILE_FRAME_HEIGHT, 0 + i * TILE_FRAME_WIDTH);
		}
	}
	//TileSprite->SelectIndex(TileMap[0][0]);
	//TileSprite->Draw(0, 0);

}
