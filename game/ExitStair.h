#pragma once
#include "GameObject.h"
class ExitStair :	public GameObject // ng chơi chạm vào object này sẽ thoát khỏi cầu thang
{ 
private:
	int width;
	int height;
	int t; // kiểu object cầu thang, 1 ở dưới, 2 ở trên

public:
	ExitStair(int X, int Y, int W, int H);
	virtual ~ExitStair();


	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera);

};

