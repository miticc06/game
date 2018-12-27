#ifndef  __BOOMERANG_H__
#define __BOOMERANG_H__


#define BOOMERANG_SPEED_X 0.3f
#define BOOMERANG_STATUS_PROCESS_1 1 // bước 1 ném theo hướng simon
#define BOOMERANG_STATUS_PROCESS_2 2 // bước 2 ném ngược hướng ban đầu
#define BOOMERANG_LIMIT_DISTANCE_X 285.0f // boomerang đi được 285px thì đổi hướng

#include "Weapon.h" 
#include "Sound.h"
class Boomerang :
	public Weapon
{
private:
	Camera *camera; 
	GSprite * _spriteIcon;
	int StatusProcess;

	float xCreate; // vị trí x boomerang lúc khởi tạo

	GameObject* simon;

public:
	Boomerang(Camera * camera, GameObject* simon);
	 
	virtual void RenderIcon(int X, int Y);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Create(float X, float Y, int Direction);

	virtual ~Boomerang();
};

#endif