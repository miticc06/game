#ifndef  __HOLLYWATER_H__
#define __HOLLYWATER_H__



#define HOLLYWATER_SPEED_X 0.24f
#define HOLLYWATER_SPEED_Y 0.25f
#define HOLYWATER_GRAVITY 0.0015f
#include "Weapon.h"
#include "Sound.h"
class HolyWater : public Weapon
{
private:
	GSprite * _spriteIcon;
	bool isCollisionBrick;



public:
	HolyWater();
	virtual ~HolyWater();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);

	void Create(float simonX, float simonY, int simonDirection);

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void UpdatePositionFitSimon();

	void RenderIcon(int X, int Y); 
	void Render(Camera *camera);
 
};



#endif  
