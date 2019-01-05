#ifndef  __HOLLYWATER_H__
#define __HOLLYWATER_H__



#define HOLLYWATER_SPEED_X 0.22f
#define HOLLYWATER_SPEED_Y 0.18f
#define HOLYWATER_GRAVITY 0.001f//5f
#include "Weapon.h"
#include "Sound.h"
class HolyWater : public Weapon
{
private:
	GSprite * _spriteIcon;
	bool isCollisionBrick;
	int CountLoop; // Số lần lặp lại việc vẽ lúc nổ Holywater.
	Camera * camera;

public:
	HolyWater(Camera * camera);
	virtual ~HolyWater();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void UpdatePositionFitSimon();
	void Attack(float X, float Y, int Direction);
	void RenderIcon(float X, float Y); 
	void Render(Camera *camera);
 
};



#endif  
