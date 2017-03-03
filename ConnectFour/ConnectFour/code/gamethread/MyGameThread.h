#pragma once
/**
* @file MyGameThread.h
* @brief ゲームスレッド
* @author 松尾裕也
* @date 2016/3/2
*/
#include "GameThread.h"
#include "../scene/SceneManager.h"
class MyGameThread :public GameThread
{
public:
	MyGameThread(IRenderer* _device);
	~MyGameThread();
	//強制終了
	void exit();
private:
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw() override;

	virtual void end() override;

	virtual bool isEnd() const override;
private:
	bool m_isEnd;
	SceneManager m_sceneManager;
};