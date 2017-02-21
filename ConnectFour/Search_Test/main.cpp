#include <iostream>
#include "Map.h"
#include "Search.h"
#include "IntVector2.h"
#include "Util.h"
int main()
{
	Map map;
	Search search;
	//map.push_back();
	//IntVector2 loc;
	//for (loc.x= 0; loc.x< MAP_SIZE;loc.x++)
	//{
	//	map.place(loc, 1);
	//}
	//map.printMap();
	//print("•]‰¿");
	//print(search.eval(&map, 1));

	//map.pop_back();
	//map.printMap();
	//print("•]‰¿");
	//print(search.eval(&map, 1));


	////IntVector2 loc;
	//for (loc.x = 0; loc.x< MAP_SIZE;loc.x++)
	//{
	//	map.place(loc, 1);
	//}
	//map.printMap();

	//print("‘Å‚Ä‚éŽè")
	//for (const auto& i: map.getFreeLoactions())
	//{
	//	print(i.x<<","<<i.y);
	//}
	//int ct = 1;
	//for (auto i = 0; i <10; i++)
	//{
	//	auto score = search.min_max(&map, ct, 3);
	//	print("min_max");
	//	print("•]‰¿:" << score);
	//	//print("X:" << score.location.x);
	//	//print("Y:" << score.location.y);
	//	//map.place(score.location, ct);
	//	map.printMap();
	//	ct=ct==1?2:1;
	//}
	/*auto score = search.min_max(&map, 1, 4);
	print("min_max");
	print("•]‰¿:" << score);*/

	int cp = 1;
	for (auto i = 0; i < 36; i++)
	{
		auto score = search.min_max(&map, 1, 2);
		auto loc = search.location;
		print("’u‚¢‚½êŠ"<< loc.x << ":" << loc.y);
		print("PLAYER"<<cp);
		print("•]‰¿"<<score);
		map.place(loc, cp);
		map.printMap();
		cp = cp == 1 ? 2 : 1;
	}


	return 0;
}