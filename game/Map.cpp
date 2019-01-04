#include "Map.h"



Map::Map()
{

}


Map::~Map()
{
	SAFE_DELETE(_sprite);
}

void Map::LoadMap(eType type)
{
	switch (type)
	{
	case eType::MAP1:
		ReadMapTXT("Resources/map/readfile_map_1.txt");
		break;
	case eType::MAP2:
		ReadMapTXT("Resources/map/readfile_map_2.txt");
		break;
	default:
		DebugOut(L"[MAP] Load map that bai!");
		return;
		break;
	}

	_texture = TextureManager::GetInstance()->GetTexture(type);
	_sprite = new GSprite(_texture, 100);

}

void Map::ReadMapTXT(char * filename)
{
	ifstream fileIn;
	fileIn.open(filename, ios::in);
	if (fileIn)
	{
		fileIn >> RowMap >> ColumnMap >> ColumnTile >> RowTile >> TotalTiles >> HeightBoard;
		for (int i = 0; i < RowMap; i++)
			for (int j = 0; j < ColumnMap; j++)
				fileIn >> TileMap[i][j];
		fileIn.close();
	}


	/*ofstream fileOut;
	int x;
	fileOut.open("C:\\Users\\MITICC06\\Desktop\\chuyendoi.txt", ios::out);
	for (int i = 0; i < RowMap; i++)
	{
		for (int j = 0; j < ColumnMap; j++)
		{
			fileOut << TileMap[i][j] + 1 << ",";

		}
		fileOut << endl;

	}

	fileOut.close();*/


}

void Map::DrawMap(Camera *camera)
{
	int row = (int)(camera->GetYCam()) / _texture->FrameHeight;
	int column = (int)(camera->GetXCam()) / _texture->FrameHeight;

	float x = -(float)((int)(camera->GetXCam()) % _texture->FrameHeight);
	float y = -(float)((int)(camera->GetYCam()) % _texture->FrameHeight);

	for (int i = 0; i < SCREEN_HEIGHT / _texture->FrameHeight + 1; i++)
		for (int j = 0; j < SCREEN_WIDTH / _texture->FrameWidth + 1; j++)
		{
			if (!(row + i < 0 || row + i >= RowMap || j + column < 0 || j + column > ColumnMap))
				_sprite->DrawFrame(TileMap[row + i][column + j], x + _texture->FrameWidth*j, y + _texture->FrameHeight*i + HeightBoard);
		}
}

int Map::GetMapWidth()
{
	return ColumnMap * _texture->FrameWidth;
}

int Map::GetMapHeight()
{
	return RowMap * _texture->FrameHeight;
}
