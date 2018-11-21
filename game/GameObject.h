#pragma once 

#include "define.h"
#include "GSprite.h"
#include "GTexture.h"
#include "Camera.h" 
#include "define.h"
#include "Object.h"

using namespace std;

 
class GameObject; 
typedef GameObject * LPGAMEOBJECT;
  
class GameObject : public Object
{
protected:
	int Health;  
	int id; // ID của object
	   
protected: 
	int trend;	// hướng -1 : trái, 1: phải
	   

public:
   
 
	GameObject();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera) = 0;
 
	int GetHealth();
	void SetHealth(int h);
	void SubHealth(int th); 
	void SetTrend(int Trend);
	int GetTrend();
	void SetId(int ID);
	int GetId();

	virtual ~GameObject();
};