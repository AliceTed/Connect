#include "LeftCommand.h"
#include "../control/IController.h"
void LeftCommand::excute(IController * _controller) const
{
	_controller->left();
}
