#include "HardAI.h"
#include "../play/desk/IDeskMediator.h"
#include "../control/PlaceTarget.h"
#include "../play/piece/Piece.h"
#include "../id/CastID.h"
#include "../util/IntVector2.h"
#include "../control/ControllerManager.h"
#include "../util/ArrayUtil.h"
const IntVector2 HardAI::NON_TARGETING = IntVector2(-1, -1);
HardAI::HardAI(std::weak_ptr<IDeskMediator> _desk, std::weak_ptr<PlaceTarget> _target, std::weak_ptr<ControllerManager>_manager)
	:m_desk(_desk),
	m_target(_target),
	m_manager(_manager),
	m_point(NON_TARGETING)
{
}

ACTION HardAI::think()
{
	assert(!m_target.expired());
	assert(!m_desk.expired());
	std::shared_ptr<PlaceTarget>target = m_target.lock();
	if (m_point != NON_TARGETING)
	{
		if (m_point == target->getPoint())
		{
			m_point = NON_TARGETING;
			return ACTION::PLACE;
		}
		return ACTION::RIGHT;
	}

	std::shared_ptr<IDeskMediator>desk = m_desk.lock();
	min_max(desk.get(), target->getControllerID(), 3);
	return ACTION::NOTHING;
}

bool HardAI::isInSide(const IntVector2 & _loc) const
{
	if (MAP_SIZE <= _loc.x)return false;
	if (_loc.x < 0)return false;
	if (MAP_SIZE <= _loc.y)return false;
	if (_loc.y < 0)return false;
	return true;
}

int HardAI::min_max(IDeskMediator * _desk, CONTROLLER_ID _id, int depth)
{
	/* 葉の場合、評価値を返す */
	if (depth <= 0) return eval(_desk, _id);

	auto next = _desk->getFreeLoactions();
	//これ以上先読みできない
	if (next.empty())return eval(_desk, _id);
	int best = -1;
	auto turn = m_manager.lock()->getActiveID();
	ArrayUtil::sort(turn,_id);
	CONTROLLER_ID nextID =*(turn.begin() + 1);
	CONTROLLER_ID selfID = m_target.lock()->getControllerID();
	for (const auto& i : next)
	{
		_desk->push_back();
		_desk->placePiece(i,_id);
		
		int score = min_max(_desk, nextID, depth - 1);
		if (best == -1)
		{
			m_point = i;
			best = score;
		}
		if (selfID == _id&& best < score)
		{
			m_point = i;
			best = score;
		}

		if (selfID != _id&& -best < -score)
		{
			m_point = i;
			best = score;
		}
		_desk->pop_back();
	}
	return best;
}

int HardAI::eval(const IDeskMediator * _desk, CONTROLLER_ID _id) const
{
	int sum = 0;
	IntVector2 location;
	for (location.x = 0; location.x < MAP_SIZE; location.x++)
	{
		for (location.y = 0; location.y < MAP_SIZE; location.y++)
		{
			sum += eval_location(_desk, location, _id);
		}
	}
	return sum;
}

int HardAI::eval_location(const IDeskMediator * _desk, const IntVector2 & _location, CONTROLLER_ID _id) const
{
	const IntVector2 dir[] =
	{
		IntVector2(1,0),//右
		IntVector2(1,1),//右上
		IntVector2(0,1),//上

		IntVector2(-1,1),//左上
		IntVector2(-1,0),//左
		IntVector2(-1,-1),//左下

		IntVector2(0,-1),//下
		IntVector2(1,-1),//右下
	};

	int score = 0;
	for (const auto& i : dir)
	{
		score += eval_dir(_desk, _location, i, _id, true);
	}
	return score;
}

int HardAI::eval_dir(const IDeskMediator * _desk, const IntVector2 & _location, const IntVector2 & _dir, CONTROLLER_ID _id, bool isReverse) const
{
	int connect = 0;
	int score = 0;
	const int scoreMap[ARRANGE_SIZE + 1] = { 0, 2,10,300,10000 };
	for (int i = 0; i < ARRANGE_SIZE; i++)
	{
		IntVector2 loc = _location + (_dir*i);
		if (!isInSide(loc))break;
		if (_desk->isFreeLocation(loc))continue;

		if (_desk->isSamePiece(loc, _id))
		{
			connect++;
			if (!isReverse)continue;
			score += eval_dir(_desk, loc, _dir*-1, _id);
			continue;
		}
		score -= 20;
		break;
	}
	return scoreMap[connect] + score;
}
