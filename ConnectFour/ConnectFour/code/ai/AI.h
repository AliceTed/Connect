#pragma once
/**
* @file AI.h
* @brief AI�p�C���^�[�t�F�C�X
* @author �����T��
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