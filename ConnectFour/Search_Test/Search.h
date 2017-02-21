#pragma once
#include "IntVector2.h"
#define ARRANGE_SIZE 4
class Map;
struct SearchScore
{
	int score;
	IntVector2 location;
};

class Search
{
public:
	Search()=default;
	~Search()=default;

	//����̋ǖʂ����ĕ]����t����(�S�Ֆʂ̑����]��)
	int eval(const Map* _map,int player);
	int min_max(Map* _map, int player, int depth);
	IntVector2 location;
private:
	//�w��ʒu�̕]��������(�w���player���Ȃ����Ă��邩�����Ȃ̂ő����]���ɓ���Ă��Ȃ�)
	int eval_location(const Map* _map, const IntVector2& _location, int player)const;
	//�ʒu�ƕ�������]�����ĕԂ�
	int eval_dir(const Map* _map, const IntVector2& _location, const IntVector2& _dir,int player,bool isReverse=false)const;
};