#include "Camera.h"

 
  


Camera::Camera(int w, int h/*, int b_left, int b_right*/)
{
	_width = w;
	_height = h;
	isAllowFollowSimon = true;
	isAutoGoX = false;
	 
	// Biên mặc định ban đầu là kích thước MAP
	_boundaryLeft = 0;
	_boundaryRight = 0;// (float)(MapWidth - SCREEN_WIDTH);
	_xCamBackup = _yCamBackup = 0;
	SetBoundaryBackup(_boundaryLeft, _boundaryRight);
	vx = 0;
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
		if (abs(_xCam - AutoGoX_Backup_X) >= AutoGoX_Distance)
		{
			_xCam = _xCam - (abs(_xCam - AutoGoX_Backup_X) - AutoGoX_Distance);
			isAutoGoX = false;
		}
	}



	if (_xCam < _boundaryLeft)
		_xCam = _boundaryLeft;

	if (_xCam > _boundaryRight)
		_xCam = _boundaryRight;

}
D3DXVECTOR2 Camera::Transform(float xWorld, float yWorld)
{
	return D3DXVECTOR2(xWorld - _xCam, yWorld - _yCam);
}

void Camera::SetPosition(float x, float y)
{
	_xCam = x;
	_yCam = y;
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

void Camera::SetAllowFollowSimon(bool b)
{
	isAllowFollowSimon = b;
}

void Camera::SetAutoGoX(float Distance, float Speed)
{
	if (isAutoGoX == true)
		return;
	vx = Speed;
	AutoGoX_Backup_X = _xCam;
	AutoGoX_Distance = Distance;
	isAutoGoX = true;
	isAllowFollowSimon = false;
}

void Camera::StopAutoGoX()
{
	isAutoGoX = false;
}

bool Camera::GetIsAutoGoX()
{
	return isAutoGoX;
}

void Camera::SetBoundary(float left, float right)
{
	_boundaryLeft = left;
	_boundaryRight = right;
}

float Camera::GetBoundaryRight()
{
	return _boundaryRight;
}

float Camera::GetBoundaryLeft()
{
	return _boundaryLeft;
}

void Camera::SetPositionBackup(float X, float Y)
{
	_xCamBackup = X;
	_yCamBackup = Y;

}

void Camera::SetBoundaryBackup(float l, float r)
{
	int ix = 0;
	_boundaryLeftBackup = l;
	_boundaryRightBackup = r;
}

void Camera::RestoreBoundary()
{
	_boundaryLeft = _boundaryLeftBackup;
	_boundaryRight = _boundaryRightBackup;
}

void Camera::RestorePosition()
{
	_xCam = _xCamBackup;
	_yCam = _yCamBackup;

	_boundaryLeft = _boundaryLeftBackup;
	_boundaryRight = _boundaryRightBackup;


}
 