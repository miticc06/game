 

#include "debug.h" 
#include "Game.h"
#include "GameObject.h"
  
GameObject::GameObject()
{
	x = y = 0;
	vx = vy = 0;
	trend = 1;	
	Health = 1;  // Alive
}

void GameObject::Update(DWORD dt, vector<LPOBJECT> *coObjects)
{
	this->dt = dt;
	dx = vx*dt;
	dy = vy*dt;
}


 

int GameObject::GetHealth()
{
	return Health;
}

void GameObject::SubHealth(int th)
{
	Health -= th;
	if (Health < 0)
		Health = 0;
}
 
void GameObject::SetTrend(int Trend)
{
	trend = Trend;
}

void GameObject::SetId(int ID)
{ 
	this->id = ID;
}
GameObject::~GameObject()
{
}
