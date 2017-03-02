#pragma once
/**
* @file NothingCommand.h
* @brief 何もしない用のコマンド
* @author 松尾裕也
* @date 2016/2/8
*/
#include "ICommand.h"
class NothingCommand :public ICommand
{
public:
	NothingCommand() = default;
	virtual void excute(IController * _controller) const override;
};