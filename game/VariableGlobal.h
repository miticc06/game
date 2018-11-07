#ifndef __Dahihi_H__
#define __Dahihi_H__
 

#include "define.h"
#include <vector>
#include "Item.h"

class VariableGlobal
{ 
public:
	static VariableGlobal * __Instance;
	static VariableGlobal * GetInstance();
	vector<Item*> ListItem;

	//vector<Item *> ListItem; // lisst chứa các item

	 

	VariableGlobal();
	~VariableGlobal();
};

#endif
