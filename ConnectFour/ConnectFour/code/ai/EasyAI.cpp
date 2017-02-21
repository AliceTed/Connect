#include "EasyAI.h"
#include "../util/Math.h"
ACTION EasyAI::think()
{
	const int LENGTH = 4;
	const ACTION map[LENGTH] = { ACTION::LEFT,ACTION::RIGHT,ACTION::PLACE,ACTION::NOTHING };
	return map[Math::random(0, LENGTH-1)];
}
