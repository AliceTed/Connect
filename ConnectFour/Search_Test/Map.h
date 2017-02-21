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
	//�܂��z�u����Ă��Ȃ��z�u�ł���ʒu��Ԃ�
	std::vector<IntVector2> getFreeLoactions()const;

	void place(const IntVector2& _location, int value);
	void push_back();
	void pop_back();
	void printMap();
private:
	//�w��̏c��ɒu����Ă��Ȃ��ꏊ�����邩
	bool isFreeSpaceCalunm(int x)const;
	//�w��̏c��ł�����Ă��Ȃ��ꏊ��Ԃ� �Ȃ��Ƃ���ERR_LOCATION
	IntVector2 freeScapeCalunm(int x)const;
	bool isCheckLocation(const IntVector2& _location)const;
private:
	using Container = std::vector<std::vector<int>>;
	Container m_map;
	std::list<Container> m_list;	
};
