#include "RightCommand.h"
#include "../control/IController.h"
void RightCommand::excute(IController * _controller) const
{
	_controller->right();
}
