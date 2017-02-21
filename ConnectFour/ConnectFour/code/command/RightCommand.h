#pragma once
/**
* @file RightCommand.h
* @brief 右移動用コマンド
* @author 松尾裕也
* @date 2016/2/8
*/
#include "ICommand.h"
class RightCommand :public ICommand
{
public:
	RightCommand() = default;
	virtual void excute(IController * _controller) const override;
};