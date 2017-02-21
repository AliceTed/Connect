#pragma once
#include <vector>
#include <list>
#include "IntVector2.h"
#define MAP_SIZE 6
#define ERR_LOCATION IntVector2(-1,-1)
class Map
{
public:
	Map();
	~Map()=default;
	bool isZero(const IntVector2& _location)const;
	bool isSame(const IntVector2& _location,int value)const;
	bool isInSide(const IntVector2& _location)const;
	//まだ配置されていなく配置できる位置を返す
	std::vector<IntVector2> getFreeLoactions()const;

	void place(const IntVector2& _location, int value);
	void push_back();
	void pop_back();
	void printMap();
private:
	//指定の縦列に置かれていない場所があるか
	bool isFreeSpaceCalunm(int x)const;
	//指定の縦列でおかれていない場所を返す ないときはERR_LOCATION
	IntVector2 freeScapeCalunm(int x)const;
	bool isCheckLocation(const IntVector2& _location)const;
private:
	using Container = std::vector<std::vector<int>>;
	Container m_map;
	std::list<Container> m_list;	
};
