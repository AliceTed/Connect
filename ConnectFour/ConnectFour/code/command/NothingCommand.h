#pragma once
/**
* @file NothingCommand.h
* @brief �������Ȃ��p�̃R�}���h
* @author �����T��
* @date 2016/2/8
*/
#include "ICommand.h"
class NothingCommand :public ICommand
{
public:
	NothingCommand() = default;
	virtual void excute(IController * _controller) const override;
};