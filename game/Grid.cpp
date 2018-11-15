#include "Grid.h"
 
Grid::Grid()
{

}
 
Grid::~Grid()
{
	//for (std::vector<GameObject*>::iterator it = listObjectGame.begin(); it != listObjectGame.end(); ++it)
	//{
	//	delete (*it);
	//} 
	//listObjectGame.clear();
}

void Grid::ReadFileToGrid(char * filename)
{
	listObjectGame.clear();
	ifstream inp;
	inp.open(filename, ios::in);
	 
	int id, type, trend, x, y, w, h, model;

	if (inp)
	{
		int n;
		inp >> n;

		for (int i = 0; i < n; i++)
		{
			inp >> id >> type >> trend >> x >> y >> w >> h >> model;
			Insert(id, type, trend, x, y, w, h, model);
		} 
		inp.close();
	} 
}

void Grid::GetListObject(vector<Object*>& ListObj, Camera * camera)
{
	ListObj.clear(); // clear list
	ResetTake();

	int rowBottom = (int) floor((camera->GetYCam() + camera->GetHeight() - 1) / (float)GRID_CELL_HEIGHT);
	int rowTop = (int)floor((camera->GetYCam() + 1) / (float)GRID_CELL_HEIGHT);

	int colLeft = (int)floor((camera->GetXCam() + 1) / (float)GRID_CELL_WIDTH);
	int colRight = (int)floor((camera->GetXCam() + camera->GetWidth() -1) / (float)GRID_CELL_WIDTH);


	for (int row = rowTop; row <= rowBottom; row++)
		for (int col = colLeft; col <= colRight; col++)
		{
			for (UINT i = 0; i < cells[row + GRID_BASE][col + GRID_BASE].size(); i++)
			{
				if (cells[row + GRID_BASE][col + GRID_BASE].at(i)->GetHealth() > 0) // còn tồn tại
				{
					if (cells[row + GRID_BASE][col + GRID_BASE].at(i)->GetIsTake() == false)
					{
						ListObj.push_back(cells[row + GRID_BASE][col + GRID_BASE].at(i));
						cells[row + GRID_BASE][col + GRID_BASE].at(i)->SetIsTake(true);
					}
				}
			}
		}
}

void Grid::GetListObject(vector<Object*> &ListObj, GameObject * obj)
{
	ListObj.clear(); // clear list
	ResetTake();

	int rowBottom = (int)floor((obj->GetY() + obj->GetHeight() -1 ) / (float)GRID_CELL_HEIGHT);
	int rowTop = (int)floor((obj->GetY()) / (float)GRID_CELL_HEIGHT);

	int colLeft = (int)floor((obj->GetX()) / (float)GRID_CELL_WIDTH);
	int colRight = (int)floor((obj->GetX() + obj->GetWidth() -1) / (float)GRID_CELL_WIDTH);


	for (int row = rowTop; row <= rowBottom; row++)
		for (int col = colLeft; col <= colRight; col++)
		{
			for (UINT i = 0; i < cells[row + GRID_BASE][col + GRID_BASE].size(); i++)
			{
				if (cells[row + GRID_BASE][col + GRID_BASE].at(i)->GetHealth() > 0) // còn tồn tại
				{
					if (cells[row + GRID_BASE][col + GRID_BASE].at(i)->GetIsTake() == false)
					{
						ListObj.push_back(cells[row + GRID_BASE][col + GRID_BASE].at(i));
						cells[row + GRID_BASE][col + GRID_BASE].at(i)->SetIsTake(true);
					}
				}
			}
		}
}
 
void Grid::ResetTake()
{
	for (UINT i = 0; i < listObjectGame.size(); i++)
	{ 
		listObjectGame[i]->SetIsTake(false);
	}
}
 
void Grid::Insert(int id, int type, int trend, int x, int y, int w, int h, int Model)
{ 
	int Top = (int) floor( y / (float)GRID_CELL_HEIGHT);
	int Bottom = (int)floor((y + h) / (float)GRID_CELL_HEIGHT);

	int Left = (int)floor(x / (float)GRID_CELL_WIDTH);
	int Right = (int)floor((x+w) / (float)GRID_CELL_WIDTH);

	GameObject * dataObject = GetNewObject(type, x, y, w, h, Model); 
	if (dataObject == NULL)
	{
		DebugOut(L"[Insert Object GRID Fail] :  Khong tao duoc object!\n");
		return;
	} 
	dataObject->SetId(id);
	dataObject->SetTrend(trend); 
	dataObject->SetIsTake(false);

	listObjectGame.push_back(dataObject);

	for (int row = Top; row <= Bottom; row++)
	{
		for (int col = Left; col <= Right; col++)
		{
			cells[row + GRID_BASE][col + GRID_BASE].push_back(dataObject);
		}
	}

}

GameObject * Grid::GetNewObject(int type, int x, int y,int w, int h, int Model)
{
	if (type == eID::BRICK) return new Brick(x, y, w, h, Model);
	if (type == eID::TORCH) return new Torch(x, y);
	if (type == eID::OBJECT_HIDDEN) return new ObjectHidden(x, y, w, h);
	if (type == eID::CANDLE) return new Candle(x, y);
	if (type == eID::STAIR) return new Stair(x, y, w, h, Model);

	return NULL;
}
 