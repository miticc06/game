#include "Camera.h"

 
  


Camera::Camera(float w, float h)
{
	_width = w;
	_height = h;


}

Camera::~Camera()
{
}

D3DXVECTOR2 Camera::Transform(int x, int y)
{
	return D3DXVECTOR2(x - viewport.x, y -viewport.y);
}

void Camera::SetPosition(int x, int y)
{
	viewport.x = x;
	viewport.y = y;
}
 

D3DXVECTOR2 Camera::GetViewport()
{
	return viewport;
}
 