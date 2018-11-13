#ifndef __OBJECT_H__
#define __OBJECT_H__



#include "define.h"
#include "GSprite.h"
#include "GTexture.h"
#include "Camera.h" 
#include "TextureManager.h"

using namespace std;


class Object;
typedef Object * LPOBJECT;

struct CollisionEvent;
typedef CollisionEvent * LPCOLLISIONEVENT;
struct CollisionEvent
{
	LPOBJECT obj;
	float t, nx, ny;
	CollisionEvent(float t, float nx, float ny, LPOBJECT obj = NULL)
	{
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->obj = obj;
	}

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};



class Object
{
protected:
	eID type; // Loại Object

	float x;
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	DWORD dt;

	GTexture * _texture;
	GSprite * _sprite;


	bool isTake;



public:
	Object();
	Object(eID _type);
	void SetPosition(float x, float y);
	void SetSpeed(float vx, float vy);
	void GetPosition(float &x, float &y);
	void GetSpeed(float &vx, float &vy);

	float GetX();
	float GetY();
	int GetHeight();
	int GetWidth();
	eID GetType();


	bool GetIsTake();
	void SetIsTake(int b);

	void RenderBoundingBox(Camera * camera);
	LPCOLLISIONEVENT SweptAABBEx(LPOBJECT coO);
	void CalcPotentialCollisions(vector<LPOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents,
		vector<LPCOLLISIONEVENT> &coEventsResult,
		float &min_tx,
		float &min_ty,
		float &nx,
		float &ny);

	 

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPOBJECT> *coObjects = NULL) = 0;
	virtual void Render(Camera * camera) = 0;


	 
	bool isCollitionObjectWithObject(Object *obj); 	// kiểm tra bằng AABB và Sweept AABB


	virtual ~Object();
};




#endif  

