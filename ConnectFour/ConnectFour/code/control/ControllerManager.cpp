#include "ControllerManager.h"
#include <cassert>
#include <algorithm>
#include "Controller.h"
#include "../util/Math.h"
ControllerManager::ControllerManager()
	:m_container(),
	m_current(nullptr),
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
	change(*m_container.begin());
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
	auto itr=std::find_if(m_container.begin(), m_container.end(), [=](ControllerPtr& _c) {return _c.get() == m_current;});
	assert(itr != m_container.end());
	itr++;
	if (itr == m_container.end())
	{
		itr = m_container.begin();
	}
	change(*itr);
}
void ControllerManager::change(ControllerPtr _next)
{
	m_current = nullptr;
	m_current = _next.get();
	m_current->start();
}