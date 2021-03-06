#pragma once
#include <memory>
#include "IScene.h"
class PlayControl;
class Title :public IScene
{
public:
	Title();
	~Title()=default;
	virtual void initialize() override;
	virtual void update(float deltaTime) override;
	virtual void draw(IRenderer * renderer) override;
	virtual void finish() override;
	virtual const SceneMode next() const override;
	virtual const bool isEnd() const override;
	virtual const bool isExit() const override;
private:
	bool m_isEnd;
	using PlayPtr = std::unique_ptr<PlayControl>;
	PlayPtr m_palyControl;
	float m_toggle;
};
