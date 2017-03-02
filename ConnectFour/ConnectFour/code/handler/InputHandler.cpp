#include "InputHandler.h"
#include "../device/Input.h"
InputHandler::InputHandler()
	:Handler()
{
}

std::weak_ptr<ICommand> InputHandler::command()
{
	const Input& input = Input::getInstance();
	if (input.keyDown(KEY::RIGHT))
	{
		return m_right;
	}
	if (input.keyDown(KEY::LEFT))
	{
		return m_left;
	}
	if (input.keyDown(KEY::SPACE))
	{
		return m_place;
	}
	return m_nothing;
}

