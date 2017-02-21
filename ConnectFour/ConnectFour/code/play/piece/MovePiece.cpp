#include "MovePiece.h"
#include "IMoving.h"
#include "InstantlyMove.h"
#include "GraduallyMove.h"
MovePiece::MovePiece(const GSvector3 & _position, CONTROLLER_ID _id, MOVING _moving)
	:Piece(_position, _id),
	m_moving(nullptr)
{
	m_moving = make_moving(_moving);
}

bool MovePiece::moveTo(const GSvector3 & _v, float _deltaTime)
{
	return m_moving->moveTo(_v, _deltaTime);
}

MovePiece::MovingPtr MovePiece::make_moving(MOVING _moving)
{
	//配列での条件分けでもよいがわざわざ必要ないものも作るのが無駄なのでスイッチで実装
	switch (_moving)
	{
	case MOVING::INSTANTLY:
		return std::make_shared<InstantlyMove>(this);
	case MOVING::GRADUALLY:
		return std::make_shared<GraduallyMove>(this);
	}
	return MovingPtr();
}
