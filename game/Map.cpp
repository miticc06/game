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
	

	//MapWidth = (TileTexture->FrameHeight)*(ColumnMatrix);  // Chiều dài của MAP
	//MapHeight = (TileTexture->FrameHeight)*(RowMatrix* +1); //  chiều cao của MAP
	
	
	ScreenColumn = Window_Width / TileTexture->FrameWidth;
	ScreenRow = Window_Height / TileTexture->FrameHeight;




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
	for (int i = 0; i < ScreenRow; i++)
	{
		for (int j = 0; j < ScreenColumn; j++)
		{
			TileSprite->SelectIndex(TileMap[i][j]);
			TileSprite->Draw(0 + j * TILE_FRAME_HEIGHT , 0 + i * TILE_FRAME_WIDTH);
		}
	}


}
