#pragma once
/**
* @file MovePiece.h
* @brief ìÆÇ©Ç∑ÉRÉ}
* @author èºîˆóTñÁ
* @date 2016/2/12
*/
#include <memory>
#include "Piece.h"
#include "MOVING.h"
class IMoving;
class MovePiece:public Piece
{
	using MovingPtr = std::shared_ptr<IMoving>;
public:
	MovePiece(const GSvector3& _position, CONTROLLER_ID _id,MOVING _moving);
	bool moveTo(const GSvector3& _v,float _deltaTime);
private:
	MovingPtr make_moving(MOVING _moving);
private:	
	MovingPtr m_moving;
private:
	class InstantlyMove;
	class GraduallyMove;
};
