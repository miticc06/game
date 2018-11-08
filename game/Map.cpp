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
	TileSprite = new GSprite(TileTexture, 100);
	

	MapWidth = (TileTexture->FrameHeight)*(ColumnMatrix);  // Chiều dài của MAP
	MapHeight = (TileTexture->FrameHeight)*(RowMatrix* +1); //  chiều cao của MAP
	
	
	ScreenColumn = Window_Width / TileTexture->FrameWidth;
	ScreenRow = Window_Height / TileTexture->FrameHeight;




}

void Map::ReadMapTXT(char * filename)
{ 
	ifstream fileIn;
	fileIn.open(filename, ios::in);

	if (fileIn)
	{
		fileIn >> RowMatrix >> ColumnMatrix >> ColTile >> RowTile >> CountTileFrame >> HeightBoard;
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

void Map::DrawMap(Camera *camera)
{ 
	row = int(camera->GetYCam()) / TileTexture->FrameHeight;
	column = int(camera->GetXCam()) / TileTexture->FrameHeight;

	x = -(int(camera->GetXCam()) % TileTexture->FrameHeight);
	y = -(int(camera->GetYCam()) % TileTexture->FrameHeight);

	for (int i = 0; i < ScreenRow; i++)
	{ 
		{
			for (int j = 0; j < ScreenColumn +1; j++) // ngay đây dư 1 nên... pla pla..
			{
				if (!(row + i < 0 || row + i>RowMatrix || j + column < 0 || j + column > ColumnMatrix))
 				{
					TileSprite->SelectIndex(TileMap[row + i][column + j]);
					TileSprite->DrawRaw(x + TileTexture->FrameWidth*j, y + TileTexture->FrameHeight*i + HeightBoard);
 				}
			}
		}
 	}
 
}
 