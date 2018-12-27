#ifndef __EFFECTMONEY_H__
#define __EFFECTMONEY_H__

#include "Effect.h"
class EffectMoney :
	public Effect
{
public:
	EffectMoney(float X, float Y, eType typeEffectMoney); 
	void Update(DWORD dt);
	virtual ~EffectMoney();
};

#endif