#pragma once
#include <memory>
#include "IScene.h"
class LoadThread;
class DataManager;
class Load :public IScene
{
public:
	Load(DataManager* _dataManager);
	~Load() = default;
	virtual void initialize() override;
	virtual void update(float deltaTime) override;
	virtual void draw(IRenderer * renderer) override;
	virtual void finish() override;
	virtual const SceneMode next() const override;
	virtual const bool isEnd() const override;
	virtual const bool isExit() const override;
private:
	bool m_isEnd;
	//DataManager* m_dataManager;
	std::shared_ptr<LoadThread>m_loader;
};
