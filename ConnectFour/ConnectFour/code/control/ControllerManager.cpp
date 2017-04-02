#include "ControllerManager.h"
#include <cassert>
#include <algorithm>
#include "Controller.h"
#include "../util/Math.h"
ControllerManager::ControllerManager()
	:m_container(),
	m_current(nullptr),
	m_currentIndex(0U),
	m_isFinish(false)
{
}

ControllerManager::~ControllerManager()
{
	m_current = nullptr;
}

void ControllerManager::initialize()
{
	m_container.clear();
	m_currentIndex = 0U;
	m_current = nullptr;
	m_isFinish=false;
}

void ControllerManager::add(ControllerPtr _controller)
{
	m_container.emplace_back(_controller);
}

void ControllerManager::start()
{
	m_isFinish =false;
	m_currentIndex = 0U;
	change(getCurrentController());
}

void ControllerManager::update(float deltaTime, const Rule& _rule)
{
	m_current->update(deltaTime);

	if (!m_current->isFinish())return;
	m_current->finish();
	m_isFinish = m_current->isWin(_rule);
	next();
}

void ControllerManager::draw(IRenderer * _renderer) const
{
	m_current->draw(_renderer);
}

bool ControllerManager::isFinish() const
{
	return m_isFinish;
}

CONTROLLER_ID ControllerManager::getCurrentID() const
{
	return m_current->getID();
}

std::vector<CONTROLLER_ID> ControllerManager::getActiveID() const
{
	std::vector<CONTROLLER_ID> res;
	for (auto i:m_container)
	{
		res.emplace_back(i->getID());
	}
	return res;
}

void ControllerManager::next()
{
	if (m_isFinish)return;
	const unsigned int size = m_container.size();
	m_currentIndex = Math::wrap(m_currentIndex + 1, 0U, size);
	change(getCurrentController());
}
void ControllerManager::change(Controller* _next)
{
	m_current = nullptr;
	m_current = _next;
	m_current->start();
}

Controller * ControllerManager::getCurrentController() const
{
	assert(m_currentIndex < m_container.size());
	assert(m_currentIndex>=0);
	return m_container.at(m_currentIndex).get();
}
