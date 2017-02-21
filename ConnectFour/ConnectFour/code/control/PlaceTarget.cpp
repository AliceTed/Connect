#include "PlaceTarget.h"
#include <gslib.h>
#include <cassert>
#include "../play/piece/MovePiece.h"
#include "../play/desk/DeskDefine.h"
PlaceTarget::PlaceTarget(CONTROLLER_ID _id)
	:m_target(nullptr),
	m_isMove(false),
	m_point(0,0,0),
	m_id(_id)
{
}

void PlaceTarget::update(float deltaTime)
{
	if (!m_isMove)return;
	m_isMove=!m_target->moveTo(m_point, deltaTime);
}

void PlaceTarget::draw(IRenderer * _renderer, float _alpha) const
{
	assert(m_target);
	m_target->draw(_renderer,_alpha);
}

void PlaceTarget::moveTo(const IntVector2 & _point ,float _zpoint)
{
	m_isMove = true;
	m_point = GSvector3(_point.x, _point.y, 0)*PIECE_SIZE;
	m_point.z = _zpoint;
}

IntVector2 PlaceTarget::getPoint() const
{
	return IntVector2(m_point.x,m_point.y)/PIECE_SIZE;
}

CONTROLLER_ID PlaceTarget::getControllerID() const
{
	return m_id;
}

void PlaceTarget::change(const IntVector2 & _point, float _zpoint, MOVING _moving)
{
	m_isMove = false;
	GSvector3 p(_point.x*PIECE_SIZE, _point.y*PIECE_SIZE,_zpoint);
	resetTarget(p,_moving);
}

bool PlaceTarget::isMove() const
{
	return m_isMove;
}

void PlaceTarget::resetTarget(const GSvector3 & _point, MOVING _moving)
{
	m_point = _point;
	m_target.reset();
	m_target = nullptr;
	m_target = std::make_shared<MovePiece>(_point, m_id, _moving);
}
