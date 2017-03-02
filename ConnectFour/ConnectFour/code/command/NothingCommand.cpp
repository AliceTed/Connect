#include "NothingCommand.h"
#include "../control/IController.h"
void NothingCommand::excute(IController * _controller) const
{
	_controller->nothing();
}
