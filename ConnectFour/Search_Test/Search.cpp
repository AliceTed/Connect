#include "Search.h"
#include <algorithm>
#include <functional>
#include <cassert>
#include "Map.h"
#include "IntVector2.h"
#include "Util.h"
int Search::eval(const Map * _map, int player)
{
	int best=static_cast<int>(-INFINITY);
	const int activeID[] = { 1,2 };
	for (auto id :activeID)
	{
		for (const auto& i : _map->getFreeLoactions())
		{
			int tmp = eval_location(_map, i, id);
			if (best < tmp)
				best = tmp;
		}
		if (id == player)
		{
			best *= 2;
		}
	}
	
	return best;
}

int Search::min_max(Map* _map,int player,int depth)
{
	/* �t�̏ꍇ�A�]���l��Ԃ� */
	if (depth <= 0) return eval(_map, player);

	auto next=_map->getFreeLoactions();
	//����ȏ��ǂ݂ł��Ȃ�
	if (next.empty())return eval(_map, player);
	const int LESS = -1000000; //static_cast<int>(-INFINITY);
	int best = LESS;
	for (const auto& i: next)
	{
		_map->push_back();
		_map->place(i, player);
		//print("�Ֆʂ̊m�F,Depth" << depth);
		//print("�z�u�����ꏊ" << i.x << ", " << i.y);
	
		//�l�K�}�b�N�X
		int score = -min_max(_map, player==1?2:1 , depth - 1);
		//if (best == LESS)best = score;
		if (best <score)
		{
			location = i;
			best = score;
		}
		assert(best!=LESS);
		//_map->printMap();
		//print("���݂̕]��" << best);
		_map->pop_back();
	}
	return best;
}

int Search::eval_location(const Map * _map, const IntVector2 & _location, int player) const
{
	const IntVector2 dir[] =
	{
		IntVector2(1,0),//�E
		IntVector2(1,1),//�E��
		IntVector2(0,1),//��

		IntVector2(-1,1),//����
		IntVector2(-1,0),//��
		IntVector2(-1,-1),//����

		IntVector2(0,-1),//��
		IntVector2(1,-1),//�E��
	};

	int score = 0;
	for (const auto& i : dir)
	{
		score += eval_dir(_map, _location, i, player,true);
	}
	return score;
}

int Search::eval_dir(const Map * _map, const IntVector2 & _location, const IntVector2 & _dir, int player, bool isReverse)const
{
	int connect = 0;
	int score = 0;
	const int scoreMap[ARRANGE_SIZE + 1] = {0, 2,10,300,10000 };
	for (int i = 0; i < ARRANGE_SIZE; i++)
	{
		IntVector2 loc = _location + (_dir*i);
		if (!_map->isInSide(loc))break;
		if (_map->isZero(loc))continue;

		if (_map->isSame(loc, player))
		{
			connect++;
			if (!isReverse)continue;
			score += eval_dir(_map, loc, _dir*-1, player);
			continue;
		}
		score -= 20;
		break;
	}
	return scoreMap[connect]+score;
}
