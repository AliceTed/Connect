#include "GamePlay.h"
#include "../play/PlayControl.h"
#include "../device/Input.h"
GamePlay::GamePlay()
	:m_palyControl(nullptr),
	m_isStop(false)
{
}

void GamePlay::initialize()
{
	m_isStop = false;
	m_palyControl = std::make_unique<PlayControl>();
	
	//m_palyControl->addEasyAI(CONTROLLER_ID::ONE);
	//m_palyControl->addEasyAI(CONTROLLER_ID::TWO);
	//
	//m_palyControl->addNormalAI(CONTROLLER_ID::ONE);
	m_palyControl->addNormalAI(CONTROLLER_ID::TWO);
	m_palyControl->addEasyAI(CONTROLLER_ID::TREE);
	//m_palyControl->addHardAI(CONTROLLER_ID::TWO);
	//m_palyControl->addNormalAI(CONTROLLER_ID::TREE);
	
	m_palyControl->addPlayer(CONTROLLER_ID::ONE);
	//m_palyControl->addPlayer(CONTROLLER_ID::TWO);
	//m_palyControl->addPlayer(CONTROLLER_ID::TREE);
	m_palyControl->start();
}

void GamePlay::update(float deltaTime)
{
	if (Input::getInstance().keyDown(KEY::S))
	{
		m_isStop = !m_isStop;
	}
	m_palyControl->update(deltaTime, m_isStop);
}

void GamePlay::draw(IRenderer * _renderer)
{
	m_palyControl->draw(_renderer);
}
#include<iostream> 
#include<fstream>
void GamePlay::finish()
{
	if (m_palyControl->isWin())
	{
		CONTROLLER_ID id = m_palyControl->getWinner();
		if (winner.count(id) == 0)
		{
			winner.insert(std::make_pair(id,0));
		}
		winner[id] += 1;
	}
	std::ofstream ofs("play.txt");
	int sum = 0;
	for (const auto& i : winner)
	{
		sum += i.second;
	}

	ofs << "‡Œv:" <<sum << std::endl;
	for (const auto& i : winner)
	{
		ofs <<"id:"<<static_cast<unsigned int>(i.first)<<",Ÿ—˜”:"<<i.second << std::endl;
	}
	m_palyControl->record();
	m_palyControl.reset();
	m_palyControl = nullptr;
}

const SceneMode GamePlay::next() const
{
	return SceneMode::GAMEPLAY;
}

const bool GamePlay::isEnd() const
{
	return  m_palyControl->isFinish()||m_palyControl->isWin();
}

const bool GamePlay::isExit() const
{
	return false;
}


