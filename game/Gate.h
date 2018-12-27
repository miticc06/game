#ifndef __GATE_H__
#define __GATE_H__

#include "GameObject.h"
#include "Sound.h"

class Gate :
	public GameObject
{
	private:
		int isStart;

public:
	Gate(float X, float Y);
	virtual ~Gate();

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(Camera * camera);
	void Start();
	int GetStart();

};


#endif
