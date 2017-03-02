#pragma once
/**
* @file PlaceTarget.h
* @brief コマの配置用クラス
* @author 松尾裕也
* @date 2016/2/12
*/
#include <memory>
#include <gslib.h>
#include "../util/IntVector2.h"
#include "../id/CONTROLLER_ID.h"

#include "../play/piece/MOVING.h"
class MovePiece;
class IRenderer;
class PlaceTarget
{
public:
	PlaceTarget(CONTROLLER_ID _id);
	~PlaceTarget()=default;
	void update(float deltaTime);
	void draw(IRenderer* _renderer,float _alpha=1.0f)const;
	void moveTo(const IntVector2& _point, float _zpoint);
	IntVector2 getPoint()const;
	CONTROLLER_ID getControllerID()const;
	void change(const IntVector2& _point, float _zpoint,MOVING _moving);

	bool isMove()const;
private:
	void resetTarget(const GSvector3& _point, MOVING _moving);
private:
	using MovePiecePtr = std::shared_ptr<MovePiece>;
	MovePiecePtr m_target;
	GSvector3 m_point;
	CONTROLLER_ID m_id;
	bool m_isMove;
};
