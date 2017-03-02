#pragma once
#include <vector>
#include "Record.h"
class CommandRecorder
{
public:
	CommandRecorder();
	~CommandRecorder()=default;

	void add(const Record& _record);
	void reset();
	void record(const std::string& _file);
private:
	using Contariner = std::vector<Record>;
	Contariner m_container;
};