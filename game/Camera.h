#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "define.h" 

class Camera
{
protected:
	 
	float _xCam;
	float _yCam;
	int _width;
	int _height;

	float vx;
	DWORD dt;

	bool isAutoGoX;
	float AutoGoX_Dx;
	float AutoGoX_Backup_X;
	bool isAllowFollowSimon; 

public:
	Camera(int w, int h/*, int b_left, int b_right*/);
	~Camera();
	 
	void Update(DWORD dt);

	D3DXVECTOR2 Transform(float, float);

	void SetPosition(float x, float y);

	float GetXCam();
	float GetYCam(); 
	int GetWidth();
	int GetHeight();

	bool checkObjectInCamera(float x, float y, float w, float h);
	bool AllowFollowSimon();

	void SetAutoGoX(float Dx, float Speed); // set các thông số auto
	bool GetIsAutoGoX();
};

#endif



