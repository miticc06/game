#include "Enemy.h"



Enemy::Enemy()
{ 
}


Enemy::~Enemy()
{
}

void Enemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt); // lưu dt, cập cập nhật dxdy
}

void Enemy::Render(Camera * camera)
{
	_sprite->Update(dt);
	  
 	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (direction == -1)
		_sprite->Draw((int)pos.x, (int)pos.y);
	else
		_sprite->DrawFlipX((int)pos.x, (int)pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
}
