#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "define.h" 

class Camera
{
protected:
	 
	float _xCam;
	float _yCam;
	
	float _xCamBackup;
	float _yCamBackup;

	int _width;
	int _height;

	float _boundaryLeft; // biên giới hạn bên trái 
	float _boundaryRight; // biên giới hạn bên phải, không bao gồm đoạn simon đi được ở cuối - Window_Width 

	//float _boundaryLeftBackup; // backup lại biên, dùng cho trường hợp simo 
	//float _boundaryRightBackup; // biên giới hạn bên phải


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
	void SetAllowFollowSimon(bool b);


	void SetAutoGoX(float Dx, float Speed); // set các thông số auto
	void StopAutoGoX();
	bool GetIsAutoGoX();

	void SetBoundary(float left, float right); // set biên giới hạn cho camera
	float GetBoundaryRight();
	float GetBoundaryLeft();

	void SetPositionBackup(float X, float Y); 
	void RestorePosition();

};

#endif



