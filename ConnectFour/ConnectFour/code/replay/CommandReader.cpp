#include "CommandReader.h"
#include<fstream>
#include<iostream>
#include<sstream>
#include <algorithm>
CommandReader::CommandReader(const std::string & _file)
	:m_container()
{
	read(_file);
}

Commands CommandReader::getCommand(CONTROLLER_ID _id) const
{
	if (m_container.count(_id) == 0)return Commands();
	return m_container.at(_id);
}

std::vector<CONTROLLER_ID> CommandReader::getActiveID() const
{
	std::vector<CONTROLLER_ID> ids;
	for (auto i:m_container)
	{
		ids.emplace_back(i.first);
	}
	return ids;
}

bool CommandReader::isEmpty() const
{
	return m_container.empty();
}

void CommandReader::registration(const Record & _record)
{
	if (isRegistration(_record.m_id))
	{
		m_container.insert(std::make_pair(_record.m_id, Commands()));
	}
	m_container[_record.m_id].emplace_back(_record.m_command);
}

void CommandReader::read(const std::string & _file)
{
	std::ifstream ifs(_file + ".csv");
	if (!ifs)return;
	std::string line;
	while (getline(ifs, line))
	{
		registration(getRecord(line));
	}
}

bool CommandReader::isRegistration(CONTROLLER_ID _id) const
{
	return m_container.count(_id) == 0;
}

Record CommandReader::getRecord(std::string _line) const
{
	std::replace(_line.begin(), _line.end(), ',', ' ');
	std::stringstream data(_line);

	unsigned int id;
	data >> id;
	unsigned int com;
	data >> com;
	return Record(static_cast<ACTION>(com), static_cast<CONTROLLER_ID>(id));
}
