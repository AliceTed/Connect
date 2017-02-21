#pragma once
#include "../ai/ACTION.h"
#include "../id/CONTROLLER_ID.h"
struct Record
{
	Record(ACTION _command,CONTROLLER_ID _id)
		:m_command(_command),m_id(_id)
	{}
	ACTION m_command;
	CONTROLLER_ID m_id;
};