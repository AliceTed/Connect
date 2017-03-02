#pragma once
/**
* @file InstantlyMove.h
* @brief ‘ã“üˆÚ“®
* @author ¼”ö—T–ç
* @date 2016/2/12
*/
#include "IMoving.h"
#include "MovePiece.h"
class MovePiece::InstantlyMove:public IMoving
{
public:
	InstantlyMove(MovePiece* _piece);
	virtual bool moveTo(const GSvector3 & _v, float deltaTime) override;
private:
	MovePiece* m_piece;
};