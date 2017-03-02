#pragma once
#include <vector>
#include "../ai/ACTION.h"
#include "Hnadler.h"
class ReplayHandler:public Handler
{
public:
	ReplayHandler(const std::vector<ACTION>& _commands);
	virtual std::weak_ptr<ICommand> command() override;
private:
	std::vector<ACTION> m_commands;
};