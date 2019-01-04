#ifndef __GATE_H__
#define __GATE_H__

#include "GameObject.h"
#include "Sound.h"

#define GATE_CLOSE 0 // trạng thái cổng đang đóng
#define GATE_OPEN_1 1 
#define GATE_OPEN_2 2 
#define GATE_OPEN_3 3 
#define GATE_OPEN_4 4

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
