#pragma once
#include "Hnadler.h"
class InputHandler:public Handler
{
public:
	InputHandler();
	virtual std::weak_ptr<ICommand> command() override;
};
