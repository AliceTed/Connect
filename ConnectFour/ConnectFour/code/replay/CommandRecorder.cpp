#include "CommandRecorder.h"
#include<iostream> 
#include<fstream>
CommandRecorder::CommandRecorder()
	:m_container()
{
}

void CommandRecorder::add(const Record & _record)
{
	m_container.emplace_back(_record);
}

void CommandRecorder::reset()
{
	m_container.clear();
}

void CommandRecorder::record(const std::string& _file)
{
	std::ofstream ofs(_file+ ".csv");
	for (const auto& i: m_container)
	{
		ofs << static_cast<unsigned int>(i.m_id) << "," << static_cast<unsigned int>(i.m_command) << std::endl;
	}
}
