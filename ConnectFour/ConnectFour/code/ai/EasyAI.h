#pragma once
/**
* @file EasyAI.h
* @brief èð®S_ÅJèo·AI
* @author ¼öTç
* @date 2016/2/8
*/
#include "AI.h"

class EasyAI:public AI
{
public:
	EasyAI()=default;
	virtual ACTION think() override;
};
