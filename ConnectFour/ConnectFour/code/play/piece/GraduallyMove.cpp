#include "GraduallyMove.h"
#include "../../util/VectorUtil.h"
const float MovePiece::GraduallyMove::EPS=0.01f;
const float MovePiece::GraduallyMove::STEP=0.1f;
MovePiece::GraduallyMove::GraduallyMove(MovePiece * _piece)
	:m_piece(_piece)
{
}

bool MovePiece::GraduallyMove::moveTo(const GSvector3 & _v, float deltaTime)
{
	m_piece->m_position=m_piece->m_position.lerp(_v, STEP);
	return VectorUtil::nearlyEqual(m_piece->m_position,_v,EPS);
}
