#include "Camera.h"

 
  


Camera::Camera(int w, int h/*, int b_left, int b_right*/)
{
	_width = w;
	_height = h;
	/*_borderLeft = b_left;
	_borderRight = b_right; */
}

Camera::~Camera()
{
}

void Camera::Update()
{
	if (_xCam < 0)
		_xCam = 0;

	if (_xCam > MapWidth - Window_Width)
		_xCam = (float)(MapWidth - Window_Width);

}
D3DXVECTOR2 Camera::Transform(float xWorld, float yWorld)
{
	return D3DXVECTOR2(xWorld - _xCam, yWorld - _yCam);
}

void Camera::SetPosition(float x, float y)
{
	_xCam = x;
	_yCam =y;
}

float Camera::GetXCam()
{
	return _xCam;
}

float Camera::GetYCam()
{
	return _yCam;
}
  

int Camera::GetWidth()
{
	return _width;
}

int Camera::GetHeight()
{
	return _height;
}
 