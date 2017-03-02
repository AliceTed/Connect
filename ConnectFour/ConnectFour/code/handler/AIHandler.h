#pragma once
#include <memory>
#include "Hnadler.h"
class AI;
using AIPtr = std::shared_ptr<AI>;
class AIHandler:public Handler
{
public:
	AIHandler(AIPtr _ai);
	virtual std::weak_ptr<ICommand> command() override;
private:
	AIPtr m_ai;
};