#pragma once
/**
* @file GameThread.h
* @brief ゲームスレッド用テンプレート
* @author 松尾裕也
* @date 2016/3/2
*/
#include "../thread/Thread.h"
class IRenderer;
class GameThread:public Thread
{
public:
	virtual void run();
protected:
	GameThread(IRenderer* _device,float _fps=60.0f);
	IRenderer* device()const;
private:
	virtual void initialize() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void draw() = 0;
	virtual void end() = 0;
	virtual bool isEnd()const = 0;
private:
	float getTime()const;
	void wait();
private:
	IRenderer* m_device;
	float m_previosTime;
	float m_frameTime;
	float m_fps;
};