#include "InstantlyMove.h"

MovePiece::InstantlyMove::InstantlyMove(MovePiece * _piece)
	:m_piece(_piece)
{
}

bool MovePiece::InstantlyMove::moveTo(const GSvector3 & _v, float deltaTime)
{
	m_piece->m_position = _v;
	return true;
}
