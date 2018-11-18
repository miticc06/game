#ifndef __PANTHER_H__
#define __PANTHER_H__

#define PANTHER_ANI_SITTING 0
#define PANTHER_ANI_RUNNING_BEGIN 1
#define PANTHER_ANI_RUNNING_END 3

#define PANTHER_SPEED_RUNNING 0.1f

#include "GameObject.h"
#include "Simon.h"

class Panther :	public GameObject
{
private:
	bool isSitting;
	bool isRunning;

public:
	Panther(float X, float Y, int Trend);
	virtual ~Panther();

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, Simon * simon,  vector<LPOBJECT> *coObjects = NULL);
	void Render(Camera *camera);

};


#endif
