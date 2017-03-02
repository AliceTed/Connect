#pragma once
#include <memory>
#include <unordered_map>
#include "IScene.h"
#include "../id/CONTROLLER_ID.h"
class PlayControl;
class GamePlay:public IScene
{
public:
	GamePlay();
	~GamePlay()=default;
	virtual void initialize() override;
	virtual void update(float deltaTime) override;
	virtual void draw(IRenderer * renderer) override;
	virtual void finish() override;
	virtual const SceneMode next() const override;
	virtual const bool isEnd() const override;
	virtual const bool isExit() const override;
private:
	using PlayPtr = std::unique_ptr<PlayControl>;
	PlayPtr m_palyControl;
	std::unordered_map<CONTROLLER_ID,int> winner;
	bool m_isStop;
};
