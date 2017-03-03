#pragma once
/**
* @file DisplayList.h
* @brief コマンド格納リスト
* @author 松尾裕也
* @date 2016/3/2
*/
#include <memory>
#include <vector>
#include "../thread/CriticalSection.h"
//class IRenderCommand;
#include "command\IRenderCommand.h"
using CommandPtr = std::unique_ptr<IRenderCommand>;
class DisplayList
{
public:
	DisplayList();
	~DisplayList()=default;
	void clear();
	//コマンドの追加(move)
	void add(CommandPtr& _command);
	//全コマンドの実行
	void render();
private:
	using CommandList = std::vector<CommandPtr>;
	CriticalSection m_lock;
	CommandList m_list;
};