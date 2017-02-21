#pragma once
/**
* @file NormalAI.h
* @brief Œ»İ‚Ì”Ô–Ú‚ğ•]‰¿‚µè‚ğl‚¦‚éAI
* @author ¼”ö—T–ç
* @date 2016/2/8
*/
#include <memory>
#include <vector>
#include "AI.h"
#include "../id/CONTROLLER_ID.h"
#include "../util/IntVector2.h"
class IDeskMediator;
class PlaceTarget;
class ControllerManager;
class NormalAI :public AI
{
	struct Score
	{
		Score(const IntVector2& _loc)
			:location(_loc), score(0) {}
		IntVector2 location;
		int score;
	};
public:
	NormalAI(std::weak_ptr<IDeskMediator> _desk,std::weak_ptr<PlaceTarget> _target, std::weak_ptr<ControllerManager>_manager);
	virtual ACTION think() override;
private:
	bool isInSide(const IntVector2& _location)const;
	int check(const IDeskMediator* _mediator, const IntVector2& _location, const IntVector2& _dir, CONTROLLER_ID _id, bool isNextCheck = false)const;
private:
	std::weak_ptr<PlaceTarget> m_target;
	std::weak_ptr<IDeskMediator> m_desk;
	std::weak_ptr<ControllerManager>m_manager;
	IntVector2 m_point;
	static const IntVector2 NON_TARGETING;
};