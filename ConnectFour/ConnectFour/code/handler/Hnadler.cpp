#include "Hnadler.h"
#include "../command/LeftCommand.h"
#include "../command/RightCommand.h"
#include "../command/PlaceCommand.h"
#include "../command/NothingCommand.h"
Handler::Handler()
	:m_left(std::make_shared<LeftCommand>()),
	m_right(std::make_shared<RightCommand>()),
	m_place(std::make_shared<PlaceCommand>()),
	m_nothing(std::make_shared<NothingCommand>())
{
}

Handler::~Handler()
{
}
