#include "Grid.h"
 
Grid::Grid()
{

}
 
Grid::~Grid()
{
	
}

void Grid::ReadFileToGrid(char * filename)
{
	listObjectGame.clear();
	ifstream inp;
	inp.open(filename, ios::in);
	 
	int id, type, trend, x, y, w, h;

	if (inp)
	{
		while (inp >> id >> type >> trend >> x >> y >> w >> h)
		{
			Insert(id, type, trend, x, y, w, h);
		}
		inp.close();
	} 
}

void Grid::GetListObject(vector<Object*>& ListObj, Camera * camera)
{
	ListObj.clear(); // clear list
	ResetTake();

	int rowBottom = (int) floor((camera->GetYCam() + camera->GetHeight()) / (float)GRID_CELL_HEIGHT);
	int rowTop = (int)floor((camera->GetYCam()) / (float)GRID_CELL_HEIGHT);

	int colLeft = (int)floor((camera->GetXCam()) / (float)GRID_CELL_WIDTH);
	int colRight = (int)floor((camera->GetXCam() + camera->GetWidth()) / (float)GRID_CELL_WIDTH);


	for (int row = rowTop; row <= rowBottom; row++)
		for (int col = colLeft; col <= colRight; col++)
		{
			for (UINT i = 0; i < cells[row + GRID_BASE][col + GRID_BASE].size(); i++)
			{
				if (cells[row + GRID_BASE][col + GRID_BASE].at(i)->GetHealth() > 0) // còn tồn tại
				{
					if (cells[row + GRID_BASE][col + GRID_BASE].at(i)->isTake == false)
					{
						ListObj.push_back(cells[row + GRID_BASE][col + GRID_BASE].at(i));
						cells[row + GRID_BASE][col + GRID_BASE].at(i)->isTake = true;
					}
				}
			}
		}
}

void Grid::GetListObject(vector<Object*> &ListObj, GameObject * obj)
{
	ListObj.clear(); // clear list
	ResetTake();

	int rowBottom = (int)floor((obj->GetY() + obj->GetHeight()) / (float)GRID_CELL_HEIGHT);
	int rowTop = (int)floor((obj->GetY()) / (float)GRID_CELL_HEIGHT);

	int colLeft = (int)floor((obj->GetX()) / (float)GRID_CELL_WIDTH);
	int colRight = (int)floor((obj->GetX() + obj->GetWidth()) / (float)GRID_CELL_WIDTH);


	for (int row = rowTop; row <= rowBottom; row++)
		for (int col = colLeft; col <= colRight; col++)
		{
			for (UINT i = 0; i < cells[row + GRID_BASE][col + GRID_BASE].size(); i++)
			{
				if (cells[row + GRID_BASE][col + GRID_BASE].at(i)->GetHealth() > 0) // còn tồn tại
				{
					if (cells[row + GRID_BASE][col + GRID_BASE].at(i)->isTake == false)
					{
						ListObj.push_back(cells[row + GRID_BASE][col + GRID_BASE].at(i));
						cells[row + GRID_BASE][col + GRID_BASE].at(i)->isTake = true;
					}
				}
			}
		}
}

 
 

void Grid::ResetTake()
{
	for (UINT i = 0; i < listObjectGame.size(); i++)
	{
		listObjectGame[i]->isTake = false;
	}
}
 
void Grid::Insert(int id, int type, int trend, int x, int y, int w, int h)
{ 
	int Top = (int) floor( y / (float)GRID_CELL_HEIGHT);
	int Bottom = (int)floor((y + h) / (float)GRID_CELL_HEIGHT);

	int Left = (int)floor(x / (float)GRID_CELL_WIDTH);
	int Right = (int)floor((x+w) / (float)GRID_CELL_WIDTH);

	GameObject * dataObject = GetNewObject(type, x, y, w, h); 
	if (dataObject == NULL)
	{
		DebugOut(L"[Insert Object GRID Fail] : Bo tay roi :v Khong tao duoc object!\n");
		return;
	} 
	dataObject->SetId(id);
	dataObject->SetTrend(trend);
	dataObject->isTake = false;

	listObjectGame.push_back(dataObject);

	for (int row = Top; row <= Bottom; row++)
	{
		for (int col = Left; col <= Right; col++)
		{
			cells[row + GRID_BASE][col + GRID_BASE].push_back(dataObject);
		}
	}

}

GameObject * Grid::GetNewObject(int type, int x, int y,int w, int h)
{
	if (type == eID::BRICK) return new Brick(x, y, w, h);
	if (type == eID::TORCH) return new Torch(x, y);
	return NULL;
}
 