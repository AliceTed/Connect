#pragma once
/**
* @file RightCommand.h
* @brief �E�ړ��p�R�}���h
* @author �����T��
* @date 2016/2/8
*/
#include "ICommand.h"
class RightCommand :public ICommand
{
public:
	RightCommand() = default;
	virtual void excute(IController * _controller) const override;
};