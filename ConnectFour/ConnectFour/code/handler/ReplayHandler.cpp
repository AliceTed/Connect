#include "ReplayHandler.h"

ReplayHandler::ReplayHandler(const std::vector<ACTION>& _commands)
	:Handler(),m_commands(_commands)
{
}

std::weak_ptr<ICommand> ReplayHandler::command()
{
	auto itr = m_commands.begin();
	if (itr == m_commands.end())return m_nothing;
	ACTION com = *itr;
	m_commands.erase(m_commands.begin());
	std::weak_ptr<ICommand> map[] = { m_left,m_right,m_place,m_nothing };
	return map[static_cast<unsigned int>(com)];
}
