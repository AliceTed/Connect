#pragma once
/**
* @file HardAI.h
* @brief 先読みAI
* @author 松尾裕也
* @date 2016/2/14
*/
#include <memory>
#include <vector>
#include "AI.h"
#include "../id/CONTROLLER_ID.h"
#include "../util/IntVector2.h"
class IDeskMediator;
class PlaceTarget;
class ControllerManager;
class HardAI :public AI
{
public:
	HardAI(std::weak_ptr<IDeskMediator> _desk, std::weak_ptr<PlaceTarget> _target ,std::weak_ptr<ControllerManager>_manager);
	virtual ACTION think() override;
private:
	int min_max(IDeskMediator* _desk,CONTROLLER_ID _id, int depth);
	//現状の局面を見て評価を付ける(全盤面の総合評価)
	int eval(const IDeskMediator* _desk, CONTROLLER_ID _id)const;
	//指定位置の評価をする(指定のplayerがつながっているかだけなので相手を評価に入れていない)
	int eval_location(const IDeskMediator* _desk, const IntVector2& _location, CONTROLLER_ID _id)const;
	//位置と方向から評価して返す
	int eval_dir(const IDeskMediator* _desk, const IntVector2& _location, const IntVector2& _dir, CONTROLLER_ID _id, bool isReverse = false)const;
private:
	std::weak_ptr<PlaceTarget> m_target;
	std::weak_ptr<IDeskMediator> m_desk;
	std::weak_ptr<ControllerManager>m_manager;
	IntVector2 m_point;
	static const IntVector2 NON_TARGETING;

};
