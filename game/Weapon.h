#ifndef __WEAPON_H__
#define	__WEAPON_H__

#include "define.h"
#include "Camera.h"
#include "GTexture.h"
#include "GSprite.h" 
#include "GameObject.h"
#include "Item.h"
#include "LargeHeart.h"
#include "UpgradeMorningStar.h"



class Weapon : public GameObject
{
protected: 
	 
	//int direction;		// hướng trái = -1, phải = 1;

	bool isFinish;

	 

public:
	Weapon();
	~Weapon();			 

	int GetDirection();
	void SetDirection(int Direction);

	virtual void Create(float simonX, float simonY, int simonDirection);
 

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL); 
 	virtual void Render(Camera *camera); 
	virtual void UpdatePositionFitSimon(); 
	virtual bool isCollision(GameObject* obj) = 0; // kiểm tra vũ khí này có va chạm với object kia hay không?

	virtual void RenderIcon(int X, int Y) = 0; 
	bool GetFinish();

	void SetFinish(bool b);
	  
	
 
};



#endif