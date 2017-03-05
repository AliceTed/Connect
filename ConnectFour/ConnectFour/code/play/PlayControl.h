#pragma once

/**
* @file PlayControl.h
* @brief Play�S�̂̊Ǘ�
* @author �����T��
* @date 2016/2/12
*/
#include <memory>
#include "../play/Rule.h"
class IRenderer;
class ControllerManager;
class Desk;
class CommandRecorder;
class PlayControl
{
public:
	PlayControl();
	~PlayControl();
	/*�Q�[���J�n*/
	void start();
	void update(float deltaTime,bool isStop=false);
	void draw(IRenderer* _renderer)const;
	bool isFinish()const;
	bool isWin()const;
	CONTROLLER_ID getWinner()const;

	void record();
public:
	void addPlayer(CONTROLLER_ID _id);
	void addEasyAI(CONTROLLER_ID _id);
	void addNormalAI(CONTROLLER_ID _id);
	void addHardAI(CONTROLLER_ID _id);
	void replay();

private:
	using DeskPtr = std::shared_ptr<Desk>;
	using ManagerPtr = std::shared_ptr<ControllerManager>;
	DeskPtr m_desk;
	Rule m_rule;
	ManagerPtr m_manager;
	std::shared_ptr<CommandRecorder> m_recorder;

	float m_time;
};