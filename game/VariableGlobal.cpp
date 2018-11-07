#include "VariableGlobal.h"

VariableGlobal * VariableGlobal::__Instance = NULL;
 
 
VariableGlobal * VariableGlobal::GetInstance()
{
	if (__Instance == NULL)
		__Instance = new VariableGlobal();
	return __Instance;
}

VariableGlobal::VariableGlobal()
{
	ListItem.clear();
	HeartCollect = 0;


 }


VariableGlobal::~VariableGlobal()
{
}
