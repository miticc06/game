#include "Dagger.h"



Dagger::Dagger()
{
	_texture = new GTexture("Resources\\weapon\\1.png");
	_sprite = new GSprite(_texture, 0);
	type = eID::DAGGER;
}


Dagger::~Dagger()
{
}

void Dagger::Update(DWORD dt, vector<LPOBJECT>* coObjects)
{  

	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;





	x += dx;

	// xử lí ra khỏi cam thì xóa
}

void Dagger::Create(float simonX, float simonY, int simonTrend)
{
	Weapon::Create(simonX, simonY + 10, simonTrend);
	vx = DAGGER_SPEED * trend;
}

void Dagger::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + _texture->FrameWidth;
	bottom = y + _texture->FrameHeight;
}

bool Dagger::isCollision(Object * obj)
{  
	// dt, dx, dy đã update

	float l, t, r, b;
	float l1, t1, r1, b1;
	this->GetBoundingBox(l, t, r, b);  // lấy BBOX của simon

	obj->GetBoundingBox(l1, t1, r1, b1);
	if (Game::GetInstance()->AABBCheck(l, t, r, b, l1, t1, r1, b1) == true)
	{
		return true; // check with AABB
	}
	 

	vector<LPOBJECT> listObject;
	listObject.clear(); 

	listObject.push_back(obj);

	vector<LPCOLLISIONEVENT> coEvents;
 
	coEvents.clear();

	CalcPotentialCollisions(&listObject, coEvents); // Lấy danh sách các va chạm
	int countCollision = (int)coEvents.size();

	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];

	return (countCollision > 0);
}

void Dagger::Render(Camera * camera)
{
	// ra khỏi cam coi như kết thúc
	// lẽ ra viết trong hàm update, nhưng ko có camera nên viết tạm ở đây
	if (x - camera->GetXCam() < 0 || x - camera->GetXCam() > camera->GetWidth())
	{
		isFinish = true;
		return; 
	}



	Weapon::Render(camera);
}
