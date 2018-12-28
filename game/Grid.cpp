#include "Grid.h"

Grid::Grid()
{
}

Grid::~Grid()
{

}

void Grid::Readfile(char * str)
{
	int id, type, direction, w, h, model, n;
	float x, y;

	ifstream inp(str, ios::in);
	inp >> n;
	for (int i = 0; i < n; i++)
	{
		inp >> id >> type >> direction >> x >> y >> w >> h >> model;
		Insert(id, type, direction, x, y, w, h, model);
	}
	inp.close();
}

GameObject * Grid::GetNewObject(int type, float x, float y, int w, int h, int Model)
{
	switch (type)
	{
	case eType::BRICK:
		return new Brick(x, y, w, h, Model);

	case eType::TORCH:
		return new Torch(x, y);

	case eType::OBJECT_HIDDEN:
		return new ObjectHidden(x, y, w, h);

	case eType::CANDLE:
		return new Candle(x, y);

	case eType::STAIR_TOP:
		return new StairTop(x, y);

	case eType::STAIR_BOTTOM:
		return new StairBottom(x, y);

	case eType::GATE:
		return new Gate(x, y);

	}
	return NULL;
}

void Grid::GetListObject(vector<GameObject*>& ListObj, Camera * camera)
{
	ListObj.clear();

	unordered_map<int, GameObject*> mapObject;

	int bottom = (int)((camera->GetYCam() + camera->GetHeight() - 1) / GRID_CELL_HEIGHT);
	int top = (int)((camera->GetYCam() + 1) / GRID_CELL_HEIGHT);

	int left = (int)((camera->GetXCam() + 1) / GRID_CELL_WIDTH);
	int right = (int)((camera->GetXCam() + camera->GetWidth() - 1) / GRID_CELL_WIDTH);


	for (int i = top; i <= bottom; i++)
		for (int j = left; j <= right; j++)
			for (UINT k = 0; k < cells[i][j].size(); k++)
			{
				if (cells[i][j].at(k)->GetHealth() > 0) // còn tồn tại
				{
					if (mapObject.find(cells[i][j].at(k)->GetId()) == mapObject.end()) // ko tìm thấy
						mapObject[cells[i][j].at(k)->GetId()] = cells[i][j].at(k);
				}
				else
				{
					//	cells[i][j].erase(cells[i][j].begin() + k); // xóa luôn
				}
			}

	for (auto& x : mapObject)
	{
		ListObj.push_back(x.second);
	}
}

void Grid::Insert(int id, int type, int direction, float x, float y, int w, int h, int Model)
{
	int top = (int)(y / GRID_CELL_HEIGHT);
	int bottom = (int)((y + h) / GRID_CELL_HEIGHT);
	int left = (int)(x / GRID_CELL_WIDTH);
	int right = (int)((x + w) / GRID_CELL_WIDTH);

	GameObject * obj = GetNewObject(type, x, y, w, h, Model);
	if (obj == NULL)
	{
		return;
	}

	obj->SetId(id);
	obj->SetDirection(direction);

	for (int i = top; i <= bottom; i++)
		for (int j = left; j <= right; j++)
			cells[i][j].push_back(obj);
}