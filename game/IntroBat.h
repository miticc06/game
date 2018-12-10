#ifndef __INTROBAT_H__
#define __INTROBAT_H__

#include "GameObject.h"
class IntroBat :
	public GameObject
{
public:
	IntroBat(float X = 0, float Y = 0, float VX = 0, float VY= 0);
	~IntroBat();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *listObject = NULL);
	void Render(Camera * camera);

};

#endif
