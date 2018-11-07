#ifndef __WEAPON_H__
#define	__WEAPON_H__

#include "define.h"
#include "Camera.h"
#include "GTexture.h"
#include "GSprite.h"
#include "DebugRenderBBOX.h"
#include <vector>
#include "GameObject.h"

class Weapon
{
protected:
	eID TypeWeapon;

 	float vx;	// Vận tốc theo trục X
	float vy;	// Vận tốc theo trục Y
	 
	int trend;		// hướng trái = -1, phải = 1;

	bool isFinish;

	float x;	// Vị trí theo trục X
	float y;	// Vị trí theo trục Y 

	GTexture * _texture;
	GSprite * _sprite;

public:
	Weapon();
	~Weapon();			 

	int GetTrend();
	void SetTrend(int Trend);

	virtual void Create(float simonX, float simonY, int simonTrend);
	virtual void Update( int dt);
 	virtual void Draw(Camera *camera);



	virtual void SetPosition(float X, float Y);
	virtual void UpdatePositionFitSimon();


	void RenderBoundingBox(Camera * camera);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void CollisionWithObject(DWORD dt, vector<LPOBJECT>* listObj) = 0;


	int GetFinish();

	void SetFinish(bool b);

	eID GetType(); 


};



#endif