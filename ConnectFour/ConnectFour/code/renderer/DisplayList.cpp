#include "DisplayList.h"
#include "command\IRenderCommand.h"
DisplayList::DisplayList()
	:m_list()
{
}

void DisplayList::clear()
{
	CriticalSection::Lock guard(m_lock);
	m_list.clear();
}

void DisplayList::add(CommandPtr & _command)
{
	CriticalSection::Lock guard(m_lock);
	m_list.emplace_back(std::move(_command));
}

void DisplayList::render()
{
	CriticalSection::Lock guard(m_lock);
	for (auto& i : m_list)i->render();
}
