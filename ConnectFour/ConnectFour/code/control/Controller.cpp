#include "Controller.h"
#include <cassert>
#include "../handler/Hnadler.h"
#include "../command/ICommand.h"
#include "../play/desk/IDeskMediator.h"
#include "../util/Math.h"
#include "../play/desk/DeskDefine.h"
#include "../renderer/IRenderer.h"
#include "../renderer/define/BasicShapeRenderDesc.h"

#include "../replay/CommandRecorder.h"
#include "../play/piece/MovePiece.h"
#include "PlaceTarget.h"
Controller::Controller(DeskMediator _deskMediator, HandlerPtr _handler ,TargetPtr _target, CONTROLLER_ID _id, RecorderPtr _recorder)
	:m_isFinish(false),
	m_deskMediator(_deskMediator),
	m_handler(_handler),
	m_target(_target),
	m_id(_id),
	m_recorder(_recorder)
{
}

void Controller::update(float deltaTime)
{
	m_target->update(deltaTime);
	if (m_target->isMove())return;
	if (m_isFinish)return;
	operation();
}
void Controller::draw(IRenderer * _renderer) const
{
	m_target->draw(_renderer,m_target->isMove()? 1.0f:0.5f);
}

void Controller::start()
{
	assert(!m_deskMediator.expired());

	m_target->change(m_deskMediator.lock()->getFreeMinimalLocation(), 1.0f, MOVING::INSTANTLY);
	m_isFinish = false;
}

void Controller::finish()
{
	m_deskMediator.lock()->placePiece(m_target->getPoint(), m_id);
}

bool Controller::isFinish() const
{
	return m_isFinish&&!m_target->isMove();
}

bool Controller::isWin(const Rule & _rule) const
{
	assert(!m_deskMediator.expired());
	return m_deskMediator.lock()->isWin(_rule,m_target->getPoint() , m_id);
}

CONTROLLER_ID Controller::getID() const
{
	return m_id;
}
void Controller::left()
{
	record(ACTION::LEFT);
	move(-1);
}

void Controller::right()
{
	record(ACTION::RIGHT);
	move(1);
}

void Controller::place()
{
	record(ACTION::PLACE);

	assert(!m_deskMediator.expired());
	std::shared_ptr<IDeskMediator> desk = m_deskMediator.lock();
	const IntVector2 current = m_target->getPoint();
	if (!desk->isFreeLocation(current))
	{
		//z=1
		m_target->moveTo(desk->getFreeMinimalLocation(),1.0f);
		return;
	}
	IntVector2 p(m_target->getPoint());
	p.y = MAP_SIZE+ SPAWN_OFFSET;
	m_target->change(p, 0, MOVING::GRADUALLY);
	m_target->moveTo(current,0.0f);
	m_isFinish = true;
}

void Controller::operation()
{
	std::weak_ptr<ICommand> handler = m_handler->command();
	if (handler.expired())return;
	handler.lock()->excute(this);
}

void Controller::move(int dir)
{
	assert(!m_deskMediator.expired());
	std::shared_ptr<IDeskMediator> desk = m_deskMediator.lock();
	IntVector2 current=m_target->getPoint();
	IntVector2 next;
	while (true)
	{
		current.x = Math::wrap(current.x + dir, 0, MAP_SIZE);
		next = desk->getFreeSpaceColumn(current.x);
		if (desk->isFreeLocation(next))
		{
			break;
		}
	}
	m_target->moveTo(next,1.0f);
}

void Controller::record(ACTION _action) const
{
	assert(!m_recorder.expired());
	m_recorder.lock()->add(Record(_action, m_id));
}

void Controller::nothing()
{
	record(ACTION::NOTHING);
}
