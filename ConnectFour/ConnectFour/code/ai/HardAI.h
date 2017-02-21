#pragma once
/**
* @file HardAI.h
* @brief ��ǂ�AI
* @author �����T��
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

	bool isInSide(const IntVector2& _loc)const;
	int min_max(IDeskMediator* _desk,CONTROLLER_ID _id, int depth);
	//����̋ǖʂ����ĕ]����t����(�S�Ֆʂ̑����]��)
	int eval(const IDeskMediator* _desk, CONTROLLER_ID _id)const;
	//�w��ʒu�̕]��������(�w���player���Ȃ����Ă��邩�����Ȃ̂ő����]���ɓ���Ă��Ȃ�)
	int eval_location(const IDeskMediator* _desk, const IntVector2& _location, CONTROLLER_ID _id)const;
	//�ʒu�ƕ�������]�����ĕԂ�
	int eval_dir(const IDeskMediator* _desk, const IntVector2& _location, const IntVector2& _dir, CONTROLLER_ID _id, bool isReverse = false)const;
private:
	std::weak_ptr<PlaceTarget> m_target;
	std::weak_ptr<IDeskMediator> m_desk;
	std::weak_ptr<ControllerManager>m_manager;
	IntVector2 m_point;
	static const IntVector2 NON_TARGETING;

};
