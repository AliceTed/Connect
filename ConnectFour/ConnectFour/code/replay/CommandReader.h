#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "../id/CONTROLLER_ID.h"
#include "../ai/ACTION.h"
#include "Record.h"
using Commands = std::vector<ACTION>;
class CommandReader
{
public:
	CommandReader(const std::string& _file);
	~CommandReader()=default;

	Commands getCommand(CONTROLLER_ID _id)const;
	std::vector<CONTROLLER_ID> getActiveID()const;
	bool isEmpty()const;
private:
	//record‚Ì“o˜^
	void registration(const Record& _record);
	void read(const std::string& _file);
	bool isRegistration(CONTROLLER_ID _id)const;
	//•¶Žš—ñ‚©‚çrecord‚É•ÏŠ·
	Record getRecord(std::string _line)const;
private:
	std::unordered_map<CONTROLLER_ID,Commands> m_container;
};