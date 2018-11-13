#ifndef __MONNEY_H__
#define __MONNEY_H__



#include "Item.h"


#define MONEY_TIMEDISPLAYMAX 5000
#define MONEY_TIMEWAITMAX 300
#define MONEY_GRAVITY 0.25f




class Monney : public Item
{
public:
	Monney(float X = 0, float Y = 0);
	~Monney();


	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPOBJECT> *listObject = NULL);



	// tong quan ve mo hinh hoa huong dịch vụ, các tp của nó và framewwork thực hiện

};




#endif // !__MONNEY_H__

