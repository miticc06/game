#include "Camera.h"

 
  


Camera::Camera(int w, int h/*, int b_left, int b_right*/)
{
	_width = w;
	_height = h;
	isAllowFollowSimon = true;
	isAutoGoX = false;
	 
}

Camera::~Camera()
{
}

void Camera::Update(DWORD dt)
{
	this->dt = dt;

	if (isAutoGoX)
	{
		float dx = vx * dt;
		_xCam += dx;
	}



	if (isAutoGoX == true)
	{
		if (abs(_xCam - AutoGoX_Backup_X) >= AutoGoX_Dx)
		{
			_xCam = _xCam - (abs(_xCam - AutoGoX_Backup_X) - AutoGoX_Dx);
			isAutoGoX = false;
		}
	}



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

bool Camera::checkObjectInCamera(float x, float y, float w, float h)
{
	if (x + w < _xCam || _xCam + _width < x)
		return false;
	if (y + h < _yCam || _yCam + _height < y)
		return false;
	return true;
}

bool Camera::AllowFollowSimon()
{
	return isAllowFollowSimon;
}

void Camera::SetAutoGoX(float Dx, float Speed)
{
	if (isAutoGoX == true)
		return;
	vx = Speed;
	AutoGoX_Backup_X = _xCam;
	AutoGoX_Dx = Dx;
	isAutoGoX = true;
	isAllowFollowSimon = false;
}

bool Camera::GetIsAutoGoX()
{
	return isAutoGoX;
}
 