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

	//Œ»ó‚Ì‹Ç–Ê‚ğŒ©‚Ä•]‰¿‚ğ•t‚¯‚é(‘S”Õ–Ê‚Ì‘‡•]‰¿)
	int eval(const Map* _map,int player);
	int min_max(Map* _map, int player, int depth);
	IntVector2 location;
private:
	//w’èˆÊ’u‚Ì•]‰¿‚ğ‚·‚é(w’è‚Ìplayer‚ª‚Â‚È‚ª‚Á‚Ä‚¢‚é‚©‚¾‚¯‚È‚Ì‚Å‘Šè‚ğ•]‰¿‚É“ü‚ê‚Ä‚¢‚È‚¢)
	int eval_location(const Map* _map, const IntVector2& _location, int player)const;
	//ˆÊ’u‚Æ•ûŒü‚©‚ç•]‰¿‚µ‚Ä•Ô‚·
	int eval_dir(const Map* _map, const IntVector2& _location, const IntVector2& _dir,int player,bool isReverse=false)const;
};