#pragma once


 

#include "define.h"
#include "GSprite.h"
#include "GTexture.h"
#include "Camera.h"
#include "DebugRenderBBOX.h"
#include "define.h"
#include "Object.h"

using namespace std;

 
class GameObject; 
typedef GameObject * LPGAMEOBJECT;
//
//struct CollisionEvent;
//typedef CollisionEvent * LPCOLLISIONEVENT;
//struct CollisionEvent
//{
//	LPGAMEOBJECT obj;
//	float t, nx, ny;
//	CollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) 
//	{ 
//		this->t = t; 
//		this->nx = nx; 
//		this->ny = ny; 
//		this->obj = obj; 
//	}
//
//	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
//	{
//		return a->t < b->t;
//	}
//};
//




class GameObject : public Object
{
protected:
	int Health; 

public:
	int id; // ID của object
	  
	int trend;	// hướng -1 : trái, 1: phải
	    
	bool isTake;

public:
   
 
	GameObject();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera) = 0;
 
	int GetHealth();
	void SubHealth(int th); 
	void SetTrend(int Trend);
	void SetId(int ID);
	  
	~GameObject();
};












/*



class GameObject
{
protected:
	int Health;
	eID type; // Loại Object


public:
	int id; // ID của object


	float x; 
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	int trend;	// hướng -1 : trái, 1: phải
	
	//int state;

	DWORD dt; 


	GTexture * _texture;
	GSprite * _sprite;
	
	bool isTake;
 
public: 
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }

	//int GetState() { return this->state; }

	void RenderBoundingBox(Camera * camera);

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);

	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);

	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents, 
		vector<LPCOLLISIONEVENT> &coEventsResult, 
		float &min_tx, 
		float &min_ty, 
		float &nx, 
		float &ny);

	//void AddAnimation(int aniId);

	GameObject();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera) = 0;
//	virtual void SetState(int state) { this->state = state; }
	
	int GetHealth();
	void SubHealth(int th);
	int GetHeight();
	int GetWidth();
	void SetTrend(int Trend);
	void SetId(int ID);

	eID GetType();




	~GameObject();
};

*/