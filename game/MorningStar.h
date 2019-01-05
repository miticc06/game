#ifndef __MORNINGSTAR_H__
#define __MORNINGSTAR_H__

#define MORNINGSTAR_TIME_WAIT_ANI 120 // thời gian chờ chuyển frame của MorningStar

#define MORNINGSTAR_ANI_LEVEL0_START 0
#define MORNINGSTAR_ANI_LEVEL0_END 3

#define MORNINGSTAR_ANI_LEVEL1_START 4
#define MORNINGSTAR_ANI_LEVEL1_END 7

#define MORNINGSTAR_ANI_LEVEL2_START 8
#define MORNINGSTAR_ANI_LEVEL2_END 11

#include "Weapon.h"
#include "GameObject.h" 
#include "LargeHeart.h"
#include "TextureManager.h"
#include "Sound.h"


class MorningStar : public Weapon
{
protected:
	int level; 
public:
	MorningStar();
	~MorningStar();
	
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(Camera *camera);


	void Attack(float X, float Y, int Direction);

	void UpdatePositionFitSimon();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void RenderIcon(float X, float Y);
 
	void UpgradeLevel();

	int GetLevel();
	bool isCollision(GameObject* obj);
};



#endif  
