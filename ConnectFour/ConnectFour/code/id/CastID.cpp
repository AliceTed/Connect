#include "CastID.h"

#include <cassert>
COLOR_ID CastID::controllerID2ColorID(CONTROLLER_ID _id)
{
	const unsigned int LENGTH= 3;
	static const COLOR_ID map[LENGTH] = { COLOR_ID::RED,COLOR_ID::BLUE,COLOR_ID::GREEN};
	const unsigned int index = static_cast<unsigned int>(_id);
	assert(LENGTH>index&&index>=0);
	return map[index];
}

GScolor4 CastID::colorID2Color(COLOR_ID _id)
{
	const unsigned int LENGTH = 4;
	static const GScolor4 map[LENGTH] = 
	{
		{1.0f,0.0f,0.0f,1.0f},
		{ 0.0f,0.0f,1.0f,1.0f },
		{0.0f,1.0f,0.0f,1.0f},
		{ 1.0f,1.0f,1.0f,1.0f}
	};
	const unsigned int index = static_cast<unsigned int>(_id);
	assert(LENGTH>index&&index >= 0);
	return map[index];
}
