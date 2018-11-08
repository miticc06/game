#ifndef __Dahihi_H__
#define __Dahihi_H__
 

#include "define.h"
 

#include "Item.h"


class VariableGlobal
{ 
public:
	static VariableGlobal * __Instance;
	static VariableGlobal * GetInstance();

 
	vector<Item*> ListItem; // lisst chứa các item
	int HeartCollect; // số lượng item heart người chơi nhặt được
	 

	VariableGlobal();
	~VariableGlobal();
};

#endif
