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

void Dagger::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{  
	Weapon::Update(dt); // update dt,dx,dy


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

bool Dagger::isCollision(GameObject * obj)
{  
	// dt, dx, dy đã update
	GameObject *gameObj = dynamic_cast<GameObject*>(obj);
	if (gameObj->GetHealth() <= 0) // vật này die rồi thì ko va chạm
		return false;

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
