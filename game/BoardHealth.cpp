#include "BoardHealth.h"



BoardHealth::BoardHealth(float X, float Y)
{
	_texture = TextureManager::GetInstance()->GetTexture(eType::BOARDHEALTH);
	_sprite = new GSprite(_texture, 0);
	this->x = X;
	this->y = Y;
} 

BoardHealth::~BoardHealth()
{ 
	SAFE_DELETE(_sprite);
}

void BoardHealth::Draw(int HealthPlayer, int HealthEnemy)
{
	HealthPlayer = min(HealthPlayer, 16);
	HealthEnemy = min(HealthEnemy, 16);

	int i, j;
	_sprite->SelectFrame(BOARDHEALTH_FRAME_PLAYER);
	for (i = 0; i < HealthPlayer; i++) 
		_sprite->Draw(x + i*_texture->GetFrameWidth(), y); 
	 
	_sprite->SelectFrame(BOARDHEALTH_FRAME_NONE);
	for (j = i; j<BOARDHEALTH_MAX_CELL; j++)
	{ 
		_sprite->Draw(x + j * _texture->GetFrameWidth(), y);
	}

	_sprite->SelectFrame(BOARDHEALTH_FRAME_ENEMY);
	for (i = 0; i < HealthEnemy; i++)
		_sprite->Draw(x + i * _texture->GetFrameWidth(), y + 18);

	_sprite->SelectFrame(BOARDHEALTH_FRAME_NONE);
	for (j = i; j < BOARDHEALTH_MAX_CELL; j++)
	{
		_sprite->Draw(x + j * _texture->GetFrameWidth(), y + 18);
	} 

}
 
