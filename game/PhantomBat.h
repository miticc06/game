#ifndef __PHANTOMBAT_H__
#define __PHANTOMBAT_H__

#include "GameObject.h"
#include "Simon.h"
#include "FireBall.h"
/*
https://www.jasondavies.com/animated-bezier/
https://en.wikipedia.org/wiki/B%C3%A9zier_curve
https://stackoverflow.com/questions/785097/how-do-i-implement-a-b%C3%A9zier-curve-in-c
https://www.desmos.com/calculator/lvdgnyhkvy
*/


#define PHANTOMBAT_PROCESS_SLEEP 0

#define PHANTOMBAT_PROCESS_START_1 1 // lúc bắt đầu, Bat di chuyển xuống
#define PHANTOMBAT_PROCESS_START_2 2 // lúc bắt đầu, Bat di chuyển đến cửa sổ (nửa vòng cung)

#define PHANTOMBAT_PROCESS_CURVES 3 // lúc di chuyển theo vòng cung

#define PHANTOMBAT_PROCESS_STRAIGHT_1 4 // xử lí di chuyển thẳng lần 1
#define PHANTOMBAT_PROCESS_STRAIGHT_2 5 // xử lí di chuyển thẳng lần 2

#define PHANTOMBAT_PROCESS_ATTACK 6 // xử lí tấn công

#define PHANTOMBAT_DEFAULT_X 5295.0f
#define PHANTOMBAT_DEFAULT_Y 90.0f

#define PHANTOMBAT_DEFAULT_HEALTH 24 // BCNN(8,12) = 24

#define PHANTOMBAT_BOUNDARY_START_STAIGHT_LEFT 5178
#define PHANTOMBAT_BOUNDARY_START_STAIGHT_RIGHT 5492



class PhantomBat : public GameObject
{
public:
	int StatusProcessing;

private:

	float xBefore;
	float yBefore;

	float xTarget;
	float yTarget;
	Simon * simon;

	/*BezierCurves*/
	bool isUseBezierCurves;
	float x1;
	float y1;

	float x2;
	float y2;

	float x3;
	float y3;

	float yLastFrame; // y của frame trước đó
	/*BezierCurves*/
	Camera *camera;


	DWORD TimeWaited; // thời gian đã chờ
	bool isWaiting;

	vector <Weapon*> * listWeaponOfEnemy;
	FireBall * weapon;

public:
	PhantomBat(Simon * simon, Camera *camera, vector <Weapon*> * listWeaponOfEnemy);
	~PhantomBat();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera);

	void Start();
	void StartCurves();
	void StartStaight();
	void StartAttack();

	float getPt(float n1, float n2, float perc);
	void Stop(); // Debug

	void ProcessSmart();

	void ResetResource();
};

#endif



