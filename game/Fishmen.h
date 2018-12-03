#ifndef __FISHMEN_H__
#define __FISHMEN_H__
 
#include "GameObject.h" 

#define FISHMEN_SPEED_Y_UP 0.4f
#define FISHMEN_SPEED_Y_DOWN 0.3f

#define FISHMEN_DY_JUMP 350 // nhảy lên khoảng 330px thì rớt xuống

#define FISHMEN_ANI_JUMP 2 // nhảy lên khoảng 330px thì rớt xuống


class Fishmen : public GameObject
{
private:
	float yInit; // vị trí y lúc khởi tạo
	bool isAllowRunAnimation;

	bool isRunning;
public:
	Fishmen(float X = 0, float Y = 0, int Direction = -1);
	virtual ~Fishmen();

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *listObject = NULL);
	void Render(Camera * camera);
};

#endif 




