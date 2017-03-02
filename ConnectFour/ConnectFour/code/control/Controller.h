#pragma once
#include <gslib.h>
#include <memory>
#include "../id/CONTROLLER_ID.h"
#include "../ai/ACTION.h"
#include "IController.h"
class PlaceTarget;
using TargetPtr = std::shared_ptr<PlaceTarget>;
class MovePiece;
class CommandRecorder;
using RecorderPtr = std::weak_ptr<CommandRecorder>;
class IRenderer;
class IDeskMediator;
using DeskMediator =std::weak_ptr<IDeskMediator>;
class Handler;
using HandlerPtr = std::shared_ptr<Handler>;
class Rule;
class Controller:public IController
{
public:
	Controller(DeskMediator _deskMediator, HandlerPtr _handler, TargetPtr _target,CONTROLLER_ID _id, RecorderPtr _recorder);
	void update(float deltaTime);
	void draw(IRenderer* _renderer)const;
	//ターンの開始時によばれる
	void start();
	//ターンの終了時によばれる
	void finish();
	//ターンが終了したか
	bool isFinish()const;

	bool isWin(const Rule& _rule)const;

	CONTROLLER_ID getID()const;
public:
	virtual void left()override;
	virtual void right() override;
	virtual void place() override;
	virtual void nothing() override;
private:
	void operation();
	void move(int dir);
	//行動を記録者に渡す
	void record(ACTION _action)const;
private:
	//ターンが終了したか？
	bool m_isFinish;
	DeskMediator m_deskMediator;
	HandlerPtr m_handler;
	TargetPtr m_target;

	CONTROLLER_ID m_id;	
	RecorderPtr m_recorder;

	static const int SPAWN_OFFSET =2;
};