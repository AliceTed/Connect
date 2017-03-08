#include "Rule.h"
#include <cassert>
#include "piece/Piece.h"
#include "../id/CastID.h"
#include "../util/IntVector2.h"

bool Rule::isWin( Container & _container, const IntVector2& _location, CONTROLLER_ID _id)const
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

bool Rule::check(Container & _container, const IntVector2 & _location, const IntVector2 & _dir, COLOR_ID _id, bool isNextCheck)const
{
	std::vector<IntVector2> connects;
	for (int i = 0; i < ARRANGE_SIZE; i++)
	{
		IntVector2 loc = _location + (_dir*i);
		if (!isInSide(loc))return false;
		if (!_container[loc.x][loc.y]->isSameType(_id))return false;
		connects.emplace_back(loc);
		if (!isNextCheck)continue;
		if (check(_container, loc, _dir*-1, _id))return true;
	}

	//繋がってい駒を適用
	assert(connects.size() == ARRANGE_SIZE);
	for (const auto& i:connects)
	{
		_container[i.x][i.y]->connect();
	}

	return true;
}