#pragma once
/**
* @file GraduallyMove.h
* @brief Lerp�ŏ��X�Ɉړ�
* @author �����T��
* @date 2016/2/12
*/
#include "IMoving.h"
#include "MovePiece.h"
class MovePiece::GraduallyMove:public IMoving
{
public:
	GraduallyMove(MovePiece* _piece);
	virtual bool moveTo(const GSvector3 & _v, float deltaTime) override;
private:
	MovePiece* m_piece;
	static const float EPS;
	static const float STEP;
};
