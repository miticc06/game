#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "define.h"

class Camera
{
protected:

//	D3DXVECTOR2 _viewport;
	float _xCam;
	float _yCam;
	int _width;
	int _height;

	/*int _borderLeft;
	int _borderRight;*/

public:
	Camera(int w, int h/*, int b_left, int b_right*/);
	~Camera();
	 
	void Update();

	D3DXVECTOR2 Transform(float, float);

	void SetPosition(float x, float y);

	float GetXCam();
	float GetYCam(); 
	int GetWidth();
	int GetHeight();

};

#endif



