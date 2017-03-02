#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>

/*
指定の配列の指定要素より前の要素を後ろに持ってくる
*/
template<class T>
void sort_back(std::vector<T>& _out, const T& _element)
{
	auto itr = std::find_if(_out.begin(), _out.end(), [_element](const T& _ele) {return _element == _ele;});
	assert(itr != _out.end());
	std::vector<T> tmp;
	std::move(_out.begin(), itr, std::back_inserter(tmp));
	_out.erase(_out.begin(), itr);
	std::move(tmp.begin(), tmp.end(), std::back_inserter(_out));
}
int main()
{
	std::vector<int>list = {0,1,2,3,4,5,6};
	int find =1;
	sort_back(list,find);
	std::cout << "確認" << std::endl;
	for (auto i :list)
	{
		std::cout << i << std::endl;
	}
	return 0;
}