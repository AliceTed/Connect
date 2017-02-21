#pragma once
#include "ICommand.h"
class PlaceCommand:public ICommand
{
public:
	PlaceCommand() = default;
	virtual void excute(IController * _controller) const override;
};
