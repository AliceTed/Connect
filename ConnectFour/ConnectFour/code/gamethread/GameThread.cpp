#include "GameThread.h"
#include <GLFW/glfw3.h>
void GameThread::run()
{
	//������
	initialize();
	//���C�����[�v
	while (!isEnd())
	{
		update(60.0f /m_fps);
		draw();
		wait();
	}
	//�I������
	end();
}

GameThread::GameThread(IRenderer * _device, float _fps)
	:m_device(_device),
	m_fps(_fps),
	m_frameTime(1.0f/ _fps),
	m_previosTime()
{
}

IRenderer * GameThread::device() const
{
	return m_device;
}

float GameThread::getTime() const
{
	return static_cast<float>(glfwGetTime());
}

void GameThread::wait()
{
	while ((getTime() - m_previosTime) < m_frameTime);
	m_previosTime = getTime();
}