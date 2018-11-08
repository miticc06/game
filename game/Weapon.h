#ifndef __WEAPON_H__
#define	__WEAPON_H__

#include "define.h"
#include "Camera.h"
#include "GTexture.h"
#include "GSprite.h"
#include "DebugRenderBBOX.h"
#include "GameObject.h"
#include "Item.h"
#include "LargeHeart.h"
#include "UpgradeMorningStar.h"



class Weapon : public Object
{
protected: 
	 
	int trend;		// hướng trái = -1, phải = 1;

	bool isFinish;

	 

public:
	Weapon();
	~Weapon();			 

	int GetTrend();
	void SetTrend(int Trend);

	virtual void Create(float simonX, float simonY, int simonTrend);
 

	virtual void Update(DWORD dt, vector<LPOBJECT> *coObjects = NULL) ;

 

 	virtual void Render(Camera *camera);

	 
	virtual void UpdatePositionFitSimon();
	 
	virtual void CollisionWithObject(DWORD dt, vector<LPOBJECT>* listObj) = 0;


	int GetFinish();

	void SetFinish(bool b);
	  
	static Item * GetNewItem(int Id, eID Type, float X, float Y);

};



#endif