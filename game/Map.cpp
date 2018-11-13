#include "Map.h"



Map::Map()
{

}


Map::~Map()
{
	SAFE_DELETE(_sprite);
}

void Map::LoadMap(eID type)
{
	switch (type)
	{
	 
	case eID::MAP1:
		ReadMapTXT("Resources/map/1.txt");
		break; 
	case eID::MAP2:
		ReadMapTXT("Resources/map/2.txt");
		break;
	default:
		DebugOut(L"[MAP] Load map that bai!");
		return;
		break;
	}

	_texture = TextureManager::GetInstance()->GetTexture(type);
	_sprite = new GSprite(_texture, 100);


	MapWidth = (_texture->FrameHeight)*(ColumnMatrix);  // Chiều dài của MAP
	MapHeight = (_texture->FrameHeight)*(RowMatrix); //  chiều cao của MAP
	
	
	ScreenColumn = Window_Width / _texture->FrameWidth;
	ScreenRow = Window_Height / _texture->FrameHeight;

}

void Map::ReadMapTXT(char * filename)
{ 
	ifstream fileIn;
	fileIn.open(filename, ios::in);
	if (fileIn)
	{
		fileIn >> RowMatrix >> ColumnMatrix >> ColTile >> RowTile >> CountTileFrame >> HeightBoard;
 		for (int i = 0; i < RowMatrix; i++)
			for (int j = 0; j < ColumnMatrix; j++)
				fileIn >> TileMap[i][j]; 
		fileIn.close(); 
	}
}

void Map::DrawMap(Camera *camera)
{ 
	row = int(camera->GetYCam()) / _texture->FrameHeight;
	column = int(camera->GetXCam()) / _texture->FrameHeight;

	x = -(int(camera->GetXCam()) % _texture->FrameHeight);
	y = -(int(camera->GetYCam()) % _texture->FrameHeight);

	for (int i = 0; i < ScreenRow; i++)
	{ 
		{
			for (int j = 0; j < ScreenColumn +1; j++) // ngay đây dư 1 nên... pla pla..
			{
				if (!(row + i < 0 || row + i>RowMatrix || j + column < 0 || j + column > ColumnMatrix))
 				{
					_sprite->SelectIndex(TileMap[row + i][column + j]);
					_sprite->Draw(x + _texture->FrameWidth*j, y + _texture->FrameHeight*i + HeightBoard);
 				}
			}
		}
 	}
 
}
 