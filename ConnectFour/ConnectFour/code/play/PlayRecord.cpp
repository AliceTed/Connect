#include "PlayRecord.h"
#include<iostream> 
#include<fstream>
PlayRecord::PlayRecord()
	:m_DrawCount(0),
	m_WinnerCount()
{
}

PlayRecord::~PlayRecord()
{
	record();
}

void PlayRecord::addWinner(CONTROLLER_ID _id)
{
	if (m_WinnerCount.count(_id) == 0)
	{
		m_WinnerCount.insert(std::make_pair(_id, 0));
	}
	m_WinnerCount[_id] += 1;
}

void PlayRecord::addDraw()
{
	m_DrawCount++;
}

int PlayRecord::calc_SumPlayCount() const
{
	int sum = m_DrawCount;
	for (const auto& i : m_WinnerCount)sum += i.second;
	return sum;
}

void PlayRecord::record()
{
	std::string path = "./asset/record/";
	std::ofstream ofs(path+"play_record.csv");
	ofs << "‡ŒvŽŽ‡”:" << calc_SumPlayCount() << std::endl;

	for (const auto& i : m_WinnerCount)
	{
		ofs << "id:" << static_cast<unsigned int>(i.first) << ",Ÿ—˜”:" << i.second << std::endl;
	}
	ofs << "ˆø‚«•ª‚¯:" <<m_DrawCount<< std::endl;
}
