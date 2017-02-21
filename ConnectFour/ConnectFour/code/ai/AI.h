#pragma once
/**
* @file AI.h
* @brief AI用インターフェイス
* @author 松尾裕也
* @date 2016/2/8
*/
#include "ACTION.h"
#include "../play/Desk/DeskDefine.h"
class AI
{
public:
	virtual ~AI() {}
	virtual ACTION think() = 0;
};