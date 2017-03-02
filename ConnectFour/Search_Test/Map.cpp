#include "Map.h"
#include <iostream>
#include <cassert>
#include "Util.h"
Map::Map()
	:m_map(),
	m_list()
{
	for (int x = 0; x < MAP_SIZE;x++)
	{
		std::vector<int> tmp;
		for (int y = 0; y < MAP_SIZE; y++)
		{
			tmp.emplace_back(0);
		}
		m_map.emplace_back(tmp);
	}
}

bool Map::isZero(const IntVector2& _location) const
{
	return m_map[_location.x][_location.y] == 0;
}

bool Map::isSame(const IntVector2& _location, int value) const
{
	return m_map[_location.x][_location.y] == value;
}

bool Map::isInSide(const IntVector2& _location) const
{
	if (_location.x < 0)return false;
	if (_location.y < 0)return false;
	if (_location.x >= MAP_SIZE)return false;
	if (_location.y >= MAP_SIZE)return false;
	return true;
}

std::vector<IntVector2> Map::getFreeLoactions() const
{
	std::vector<IntVector2> res;
	for (auto x = 0; x < MAP_SIZE; x++)
	{
		if (isFreeSpaceCalunm(x))
		{
			res.emplace_back(freeScapeCalunm(x));
		}
	}
	return res;
}

bool Map::isFreeSpaceCalunm(int x) const
{
	//重力付きなので一番上が置かれているかで判断できる
	return m_map[x][MAP_SIZE - 1] == 0;
}

IntVector2 Map::freeScapeCalunm(int x) const
{
	if (!isFreeSpaceCalunm(x))return ERR_LOCATION;
	IntVector2 loc(x, 0);
	for (loc.y = 0; loc.y < MAP_SIZE; loc.y++)
	{
		if (isZero(loc))
		{
			return loc;
		}
	}
	return ERR_LOCATION;
}

bool Map::isCheckLocation(const IntVector2& _location) const
{
	for (const auto& i : getFreeLoactions())
	{
		if (_location == i)
		{
			return true;
		}
	}
	return false;
}

void Map::place(const IntVector2& _location, int value)
{
	assert(isInSide(_location));
	assert(isCheckLocation(_location));
	m_map[_location.x][_location.y] = value;
}

void Map::push_back()
{
	m_list.emplace_back(m_map);
	//print("マップを保存");
	//print("保存数:" << m_list.size());
}

void Map::pop_back()
{
	m_map = m_list.back();
	m_list.pop_back();
	//print("マップを再帰");
	//print("保存数:" << m_list.size());
}

void Map::printMap()
{
	std::cout << "PRINT_MAP" << std::endl;

	for (int y = 0; y < MAP_SIZE; y++)
	{
		for (int x = 0; x < MAP_SIZE;x++)
		{
			std::cout << m_map[x][y] << " ";
		}
		std::cout << std::endl;
	}
}
