#pragma once
/**
* @file Piece.h
* @brief ÉRÉ}
* @author èºîˆóTñÁ
* @date 2016/2/8
*/
#include <gslib.h>
#include "../../id/COLOR_ID.h"
#include "../../id/CONTROLLER_ID.h"
class IRenderer;
class Piece
{
public:
	//colorIDíºê⁄éwíË
	Piece(const GSvector3& _position,COLOR_ID _id);
	//controllerIDÇ©ÇÁïœä∑
	Piece(const GSvector3& _position, CONTROLLER_ID _id);
	virtual ~Piece();
	virtual void update(float deltaTime);
	virtual void draw(IRenderer* _renderer,float _alpha=1.0f)const;
	bool isSameType(COLOR_ID _id)const;
protected:
	GSvector3 m_position;
private:
	COLOR_ID m_color;
	float m_rotateY;
	float m_rotSpeed;
};