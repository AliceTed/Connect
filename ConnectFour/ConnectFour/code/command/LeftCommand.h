#pragma once
/**
* @file LeftCommand.h
* @brief ���ړ��p�R�}���h
* @author �����T��
* @date 2016/2/8
*/
#include "ICommand.h"
class LeftCommand:public ICommand
{
public:
	LeftCommand()=default;
	virtual void excute(IController * _controller) const override;
};
