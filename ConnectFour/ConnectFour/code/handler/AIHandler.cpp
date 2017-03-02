#include "AIHandler.h"
#include "../ai/AI.h"
AIHandler::AIHandler(AIPtr _ai)
	:Handler(),
	m_ai(_ai)
{
}

std::weak_ptr<ICommand> AIHandler::command()
{
	std::weak_ptr<ICommand> map[] = {m_left,m_right,m_place,m_nothing};
	return map[static_cast<unsigned int>(m_ai->think())];
	/*switch (m_ai->think())
	{
	case ACTION::PLACE:
		return m_place;
	case ACTION::RIGHT:
		return m_right;
	case ACTION::LEFT:
		return m_left;
	}
	return std::weak_ptr<ICommand>();*/
}
