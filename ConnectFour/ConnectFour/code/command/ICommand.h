#pragma once
class IController;
class ICommand
{
public:
	virtual ~ICommand() {}
	virtual void excute(IController* _controller)const=0;
};