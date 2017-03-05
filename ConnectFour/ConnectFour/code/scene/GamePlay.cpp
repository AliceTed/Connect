#include "GamePlay.h"
#include "../play/PlayControl.h"
#include "../device/Input.h"
GamePlay::GamePlay()
	:m_palyControl(nullptr),
	m_isStop(false),
	m_record()
{
}

void GamePlay::initialize()
{
	m_isStop = false;
	m_palyControl = std::make_unique<PlayControl>();
	
	//m_palyControl->addEasyAI(CONTROLLER_ID::ONE);
	//m_palyControl->addEasyAI(CONTROLLER_ID::TWO);
	//
	m_palyControl->addNormalAI(CONTROLLER_ID::ONE);
	m_palyControl->addNormalAI(CONTROLLER_ID::TWO);
	m_palyControl->addEasyAI(CONTROLLER_ID::TREE);
	//m_palyControl->addHardAI(CONTROLLER_ID::TWO);
	//m_palyControl->addNormalAI(CONTROLLER_ID::TREE);
	
	//m_palyControl->addPlayer(CONTROLLER_ID::ONE);
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

void GamePlay::finish()
{
	if (m_palyControl->isWin())
	{
		m_record.addWinner(m_palyControl->getWinner());
	}
	if (m_palyControl->isFinish())
	{
		m_record.addDraw();
	}

	//ƒfƒXƒgƒ‰ƒNƒ^‚Å‹L˜^‚µ‚È‚¢‚Ì‚ÍŽŽ‡’†‚ÉƒQ[ƒ€‚ð‚â‚ß‚½ê‡‚É‹L˜^‚³‚ê‚é‚Ì‚ð–h‚®‚½‚ß
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


