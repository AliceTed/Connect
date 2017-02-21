#include "Rule.h"
#include "piece/Piece.h"
#include "../id/CastID.h"
#include "../util/IntVector2.h"

bool Rule::isWin(const Container & _container, const IntVector2& _location, CONTROLLER_ID _id)const
{
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

	COLOR_ID color = CastID::controllerID2ColorID(_id);

	for (const auto& i: dir)
	{
		if (check(_container, _location,i, color, true))return true;
	}
	return false;
}

bool Rule::isInSide(const IntVector2 & _location) const
{
	if (MAP_SIZE <= _location.x)return false;
	if (_location.x <0)return false;
	if (MAP_SIZE<=_location.y)return false;
	if (_location.y < 0)return false;
	return true;
}

bool Rule::check(const Container & _container, const IntVector2 & _location, const IntVector2 & _dir, COLOR_ID _id, bool isNextCheck)const
{
	for (int i = 0; i < ARRANGE_SIZE; i++)
	{
		IntVector2 loc = _location + (_dir*i);
		if (!isInSide(loc))return false;
		if (!_container[loc.x][loc.y]->isSameType(_id))return false;
		if (!isNextCheck)continue;
		if (check(_container, loc, _dir*-1, _id))return true;
	}
	return true;
}