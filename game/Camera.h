#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "define.h"

class Camera
{
protected:
	D3DXVECTOR2 viewport;
	int _width;
	int _height;


public:
	Camera(float w, float h);
	~Camera();
	 


	D3DXVECTOR2 Transform(int x, int y);

	void SetPosition(int x, int y); 

	D3DXVECTOR2 GetViewport();


};

#endif



