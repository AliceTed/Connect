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

	//現状の局面を見て評価を付ける(全盤面の総合評価)
	int eval(const Map* _map,int player);
	int min_max(Map* _map, int player, int depth);
	IntVector2 location;
private:
	//指定位置の評価をする(指定のplayerがつながっているかだけなので相手を評価に入れていない)
	int eval_location(const Map* _map, const IntVector2& _location, int player)const;
	//位置と方向から評価して返す
	int eval_dir(const Map* _map, const IntVector2& _location, const IntVector2& _dir,int player,bool isReverse=false)const;
};