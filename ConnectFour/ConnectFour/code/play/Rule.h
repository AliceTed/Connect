#pragma once
#include "Desk/DeskDefine.h"
#include "../id/CONTROLLER_ID.h"
#include "../id/COLOR_ID.h"
#include "../util/IntVector2.h"
//struct IntVector2;
class Rule
{
public:
	Rule()=default;
	~Rule()=default;

	bool isWin(Container& _container,const IntVector2& _location, CONTROLLER_ID _id)const;
private:
	bool isInSide(const IntVector2& _location)const;
	bool check( Container& _container, const IntVector2& _location, const IntVector2& _dir, COLOR_ID _id,bool isNextCheck=false)const;
};