#pragma once
/**
* @file EasyAI.h
* @brief ������S�����_���ŌJ��o��AI
* @author �����T��
* @date 2016/2/8
*/
#include "AI.h"

class EasyAI:public AI
{
public:
	EasyAI()=default;
	virtual ACTION think() override;
};
