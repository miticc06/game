#ifndef __ITEM_H__
#define __ITEM_H__

#include "GSprite.h"
#include "Camera.h"
#include "GTexture.h"
#include "GameObject.h" 
#include "define.h" 

class Item : public Object
{
protected: 

	DWORD TimeDisplayMax; // thời gian tối đa cho phép hiển thị.
	DWORD TimeDisplayed; // Thời gian đã hiển thị.

	DWORD TimeWaited; // Thời gian đã chờ trước khi hiển thị
	DWORD TimeWaitMax; // Thời gian tối đa phải chờ trước khi hiển thị

	bool isFinish; // đã kết thúc chưa?

public:
	Item();
	~Item();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPOBJECT> *listObject = NULL);
	virtual void Render(Camera * camera);
	virtual bool isWaitingDisplay(); // đang chờ object hiển thi? - simon chưa được ăn
 
 	bool GetFinish();
	void SetFinish(bool b);
};




















#endif // !__ITEM_H__




