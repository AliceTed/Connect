#pragma once
/**
* @file HardAI.h
* @brief æ“Ç‚İAI
* @author ¼”ö—T–ç
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
	//Œ»ó‚Ì‹Ç–Ê‚ğŒ©‚Ä•]‰¿‚ğ•t‚¯‚é(‘S”Õ–Ê‚Ì‘‡•]‰¿)
	int eval(const IDeskMediator* _desk, CONTROLLER_ID _id)const;
	//w’èˆÊ’u‚Ì•]‰¿‚ğ‚·‚é(w’è‚Ìplayer‚ª‚Â‚È‚ª‚Á‚Ä‚¢‚é‚©‚¾‚¯‚È‚Ì‚Å‘Šè‚ğ•]‰¿‚É“ü‚ê‚Ä‚¢‚È‚¢)
	int eval_location(const IDeskMediator* _desk, const IntVector2& _location, CONTROLLER_ID _id)const;
	//ˆÊ’u‚Æ•ûŒü‚©‚ç•]‰¿‚µ‚Ä•Ô‚·
	int eval_dir(const IDeskMediator* _desk, const IntVector2& _location, const IntVector2& _dir, CONTROLLER_ID _id, bool isReverse = false)const;
private:
	std::weak_ptr<PlaceTarget> m_target;
	std::weak_ptr<IDeskMediator> m_desk;
	std::weak_ptr<ControllerManager>m_manager;
	IntVector2 m_point;
	static const IntVector2 NON_TARGETING;

};
