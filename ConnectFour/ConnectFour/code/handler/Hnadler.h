#pragma once
/**
* @file Handler.h
* @brief コマンドを扱う親クラス
* @author 松尾裕也
* @date 2016/2/8
*/
#include <memory>
class ICommand;
class Handler
{
public:
	Handler();
	virtual ~Handler();
	virtual std::weak_ptr<ICommand> command()=0;
protected:
	using CommandPtr = std::shared_ptr<ICommand>;
	CommandPtr m_left;
	CommandPtr m_right;
	CommandPtr m_place;
	CommandPtr m_nothing;
};