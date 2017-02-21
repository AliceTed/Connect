#include "PlaceCommand.h"
#include "../control/IController.h"
void PlaceCommand::excute(IController * _controller) const
{
	_controller->place();
}
