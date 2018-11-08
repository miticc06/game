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
	if (_viewport.x < 0)
		_viewport.x = 0;

	if (_viewport.x > MapWidth - Window_Width)
		_viewport.x = MapWidth - Window_Width; 

}
D3DXVECTOR2 Camera::Transform(float x, float y)
{
	return D3DXVECTOR2(x - _viewport.x, y - _viewport.y);
}

void Camera::SetPosition(int x, int y)
{
	_viewport.x = x;
	_viewport.y = y;
}
 

D3DXVECTOR2 Camera::GetViewport()
{
	return _viewport;
}

int Camera::GetWidth()
{
	return _width;
}

int Camera::GetHeight()
{
	return _height;
}
 