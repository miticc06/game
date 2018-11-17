#include "Dagger.h"



Dagger::Dagger()
{
 	_texture = TextureManager::GetInstance()->GetTexture(eID::DAGGER);
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

void Dagger::RenderIcon(int X, int Y)
{
	_sprite->DrawFlipXIndex(0, X, Y); 

}

bool Dagger::isCollision(Object * obj)
{  
	// dt, dx, dy đã update

	return isCollitionObjectWithObject(obj);
}

void Dagger::Render(Camera * camera)
{
	// ra khỏi cam coi như kết thúc
	// lẽ ra viết trong hàm update, nhưng ko có camera nên viết tạm ở đây
	if (x - camera->GetXCam() + _sprite->_texture->FrameWidth < 0 || x - camera->GetXCam() > camera->GetWidth())
	{
		isFinish = true;
		return; 
	}



	Weapon::Render(camera);
}
