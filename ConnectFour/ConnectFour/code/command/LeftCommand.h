#pragma once
/**
* @file LeftCommand.h
* @brief 左移動用コマンド
* @author 松尾裕也
* @date 2016/2/8
*/
#include "ICommand.h"
class LeftCommand:public ICommand
{
public:
	LeftCommand()=default;
	virtual void excute(IController * _controller) const override;
};
