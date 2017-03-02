#include "NormalAI.h"
#include <cassert>
#include <algorithm>
#include "../play/desk/IDeskMediator.h"
#include "../control/PlaceTarget.h"
#include "../play/piece/Piece.h"
#include "../id/CastID.h"
#include "../util/IntVector2.h"
#include "../control/ControllerManager.h"
const IntVector2 NormalAI::NON_TARGETING=IntVector2(-1,-1);
NormalAI::NormalAI(std::weak_ptr<IDeskMediator> _desk, std::weak_ptr<PlaceTarget> _target, std::weak_ptr<ControllerManager>_manager)
	:m_desk(_desk),
	m_target(_target),
	m_manager(_manager),
	m_point(NON_TARGETING)
{
}

ACTION NormalAI::think()
{
	assert(!m_target.expired());
	assert(!m_desk.expired());
	assert(!m_manager.expired());
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

	const IntVector2 dir[] =
	{
		IntVector2(1,0),//âE
		IntVector2(1,1),//âEè„
		IntVector2(0,1),//è„

		IntVector2(-1,1),//ç∂è„
		IntVector2(-1,0),//ç∂
		IntVector2(-1,-1),//ç∂â∫

		IntVector2(0,-1),//â∫
		IntVector2(1,-1),//âEâ∫
	};

	std::vector<Score> score;
	std::vector<CONTROLLER_ID> active=m_manager.lock()->getActiveID();
	for (auto id : active)
	{
		std::vector<Score> excute;
		for (auto i:desk->getFreeLoactions())
		{
			excute.emplace_back(Score(i));
		}
		for (auto& i : excute)
		{
			i.score = 0;
			for (const auto& d : dir)
			{
				i.score += check(desk.get(), i.location, d,id, true);
			}
		}
		std::sort(excute.begin(), excute.end(), [](const Score& s1, const Score& s2) {return s1.score > s2.score;});
		Score first = *excute.begin();
		if (target->getControllerID() == id)
		{
			first.score *= 2.5f;
		}
		score.emplace_back(first);
	}

	std::sort(score.begin(), score.end(), [](const Score& s1, const Score& s2) {return s1.score > s2.score;});
	m_point = (*score.begin()).location;
	return ACTION::NOTHING;
}

bool NormalAI::isInSide(const IntVector2 & _location) const
{
	if (MAP_SIZE <= _location.x)return false;
	if (_location.x < 0)return false;
	if (MAP_SIZE <= _location.y)return false;
	if (_location.y < 0)return false;
	return true;
}

int NormalAI::check(const IDeskMediator* _mediator,const IntVector2 & _location, const IntVector2 & _dir, CONTROLLER_ID _id, bool isNextCheck) const
{
	int straight = 0;
	int score = 0;
	for (int i = 0; i < ARRANGE_SIZE; i++)
	{
		IntVector2 loc = _location + (_dir*i);
		if (!isInSide(loc))break;

		if (_mediator->isFreeLocation(loc))continue;
		if (_mediator->isSamePiece(loc,_id))
		{
			straight++;
			if (!isNextCheck)continue;
			score += check(_mediator, loc, _dir*-1, _id);
			continue;
		}
		score -= 20;
		break;
	}

	const int scoreMap[ARRANGE_SIZE] = { 2,10,300,10000 };
	score += scoreMap[straight];
	return score;
}