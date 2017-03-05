#pragma once
#include <memory>
#include "IScene.h"
#include "../play/PlayRecord.h"
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
	PlayRecord m_record;
	bool m_isStop;
};
